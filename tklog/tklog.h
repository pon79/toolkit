#ifndef TKLOG_H
#define TKLOG_H

#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QEvent>
#include <QLoggingCategory>
#include <QObject>
#include <QStandardPaths>

namespace ToolKit {
namespace Log {

// in main
//#ifdef use_TKlog
//qInstallMessageHandler(ToolKit::Log::messageHandler);
//#endif

/*!
 * \brief Message handler Qt.
 *
 */
static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{

    #ifndef QT_DEBUG
    if ( type == QtDebugMsg )
        return;
    #endif

    QString configLocation =
        QStandardPaths::standardLocations(QStandardPaths::GenericConfigLocation).first();
    QString organizationName = QCoreApplication::organizationName().remove(QChar(' '));
    QString applicationName  = QCoreApplication::applicationName().remove(QChar(' '));

    QDir logDir{ configLocation + (configLocation.isEmpty() ? "" : "/") + organizationName +
                 (organizationName.isEmpty() ? "" : "/") + applicationName +
                 (applicationName.isEmpty() ? "" : "/") + "logs" };


    if ( logDir.exists() )
    {
        // if there are more than 30 log files, then delete the 10 earliest log files
        auto fileList = logDir.entryList( QDir::NoDotAndDotDot	| QDir::NoSymLinks	| QDir::Files, QDir::Time);

        if( fileList.size() > 30 )
        {
            auto it{ --fileList.end() };
            for( int i = 0 ; i < 10 ; i++, --it)
                QFile::remove( logDir.absolutePath() + '/' + *it );
        }
    }
    else
    {
        if ( logDir.mkpath(logDir.absolutePath()) )
            qInfo() << "Create directory" << logDir.absolutePath();
        else
            qWarning() << "Failed to create logging directory: " << logDir.absolutePath();
    }


    QFile logFile(logDir.path() + '/' + QDate::currentDate().toString(Qt::ISODate));


    // set the maximum size of the log file = 5 MB
    if( logFile.size() > 5000000 )
    {
        if (!logFile.open(QIODevice::WriteOnly | QIODevice::Text))
            qWarning() << "failed to open logFile";
    }
    else
    {
        if (!logFile.open(QIODevice::Append | QIODevice::Text))
            qWarning() << "failed to open logFile";
    }


    QTextStream out(&logFile);

    out << QDateTime::currentDateTime().toString(Qt::ISODate) << '>';

    switch (type) {
    case QtDebugMsg:
        out << " DEBUG   ";
        break;
    case QtWarningMsg:
        out << " WARNING ";
        break;
    case QtCriticalMsg:
        out << " CRITICAL";
        break;
    case QtFatalMsg:
        out << " FATAL   ";
        break;
    case QtInfoMsg:
        out << " INFO    ";
    }

    #ifdef QT_DEBUG

    QString functionName{ context.function };

    // EXAMPLE functionName int MainWindow::arrInfoUpdate(const QByteArray&)

    // cutting off arguments
    functionName = functionName.split("(").first();

    // if there is a return value, then we cut it off
    if (functionName.contains(' '))
        functionName = functionName.split(' ').last();

    // only the class name and the function name should remain
    out << " [" << functionName << "] ";

    // duplicated in the operating system console
    qDebug().noquote() << '[' << functionName << ']' << msg;

    #endif // QT_DEBUG

    // write a message to a file
    out << msg << endl;

    out.flush();
    logFile.close();
} // end messageHandler

} //  end namespace Log
} // end namespace ToolKit

#endif // TKLOG_H
