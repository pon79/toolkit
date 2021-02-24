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

// нужно добавить в main
//#ifdef use_TKlog
//qInstallMessageHandler(ToolKit::Log::messageHandler);
//#endif

/*!
 * \brief Обработчик сообщений Qt.
 *
 * Файлы логирования пишутся в каталог пользовательских настроек /home/user/.config
 * в папку с названием компании + название программы.
 * В режиме debug к сообщениям добавлены название класса и название функции.
 * В режиме release вывод в консоль операционной системы не осуществляется.
 * \param type тип сообщения: qDebug(), qInfo(), qWarning(), qCritical(), qFatal()
 * \param context информация о сообщении (прототип функции и пр.)
 * \param msg текст сообщения
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
        // если лог-файлов в папке более 30, то удалим 10 самых ранних лог-файлов
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


    // установим максимальный размер лог-файла = 5 Мбайт
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

    // ПРИМЕР functionName int MainWindow::arrInfoUpdate(const QByteArray&)

    // отсекаем аргументы
    functionName = functionName.split("(").first();

    // если есть возвращаемое значение, то и его отсекаем
    if (functionName.contains(' '))
        functionName = functionName.split(' ').last();

    // должны были остаться только название класса и название функции
    out << " [" << functionName << "] ";

    // дублируем в консоль операционной системы
    qDebug().noquote() << '[' << functionName << ']' << msg;

    #endif // QT_DEBUG

    // записываем сообщение в файл
    out << msg << endl;

    out.flush();
    logFile.close();
} // end messageHandler

} //  end namespace Log
} // end namespace ToolKit

#endif // TKLOG_H
