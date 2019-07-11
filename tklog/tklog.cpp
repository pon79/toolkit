#include "tklog.h"

#include <QCoreApplication> // qApp->applicationName
#include <QDate>
#include <QDir>



TKlog::TKlog( )
{
}

void TKlog::messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // если каталог нашего приложения не существует, то создаём его в домашней папке пользователя
    QDir logDir{ QDir::homePath() + '/' + qApp->applicationName().remove(' ') + "/log" };

    if ( !logDir.exists() )
        if ( !logDir.mkpath( logDir.path() ) )
             qWarning() << "failed to create logging directory";

    // создаём новый файл c указанием даты создания
    QFile logFile( logDir.path() + "/log_" + QDate::currentDate().toString( Qt::ISODate ) );

    if (!logFile.open(QIODevice::Append | QIODevice::Text ))
        qWarning() << "failed to open logFile";

    QTextStream out( &logFile );

    // указываем дату и время записи
    out << QDateTime::currentDateTime().toString(Qt::ISODate ); /*<<*//* QTime::currentTime().toString()*/;

    // По типу определяем, к какому уровню относится сообщение
    switch (type)
    {
    case QtInfoMsg:     out << " INFO"; break;
    case QtDebugMsg:    out << " DEBUG"; break;
    case QtWarningMsg:  out << " WARNING"; break;
    case QtCriticalMsg: out << " CRITICAL\n"; break;
    case QtFatalMsg:    out << " FATAL\n";
    }

    #ifdef QT_DEBUG
    // в режиме DEBUG перед сообщением пишем название функции

    QString functionName{context.function};

    if ( functionName.contains("::") )
            functionName = functionName.split("::")[ 1 ];

    functionName = functionName.split("(").first();

    if ( functionName.contains(' ') )
            functionName = functionName.split(' ')[ 1 ];

    out << ": " << functionName;
    qDebug() << functionName << ':'  << msg; // дублируем в консоль
    #endif

    // записываем сообщение
    out << msg << endl;

    out.flush();    // Очищаем буферизированные данные
    logFile.close();
}
