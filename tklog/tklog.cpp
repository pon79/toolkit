#include "tklog.h"

#include <QApplication> // qApp->applicationName
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
    {
        if ( logDir.mkpath( logDir.path() ) )
            qInfo() << "created logging directory";
        else
            qWarning() << "failed to create logging directory";
    }

    // каждый день создаём новый файл логирования
    QFile logFile( logDir.path() + "/log_" + QDate::currentDate().toString( Qt::ISODate ) );

    if (!logFile.open(QIODevice::Append | QIODevice::Text ))
        qWarning() << "failed to open logFile";

    QTextStream out( &logFile );

    // указываем время записи
    out << QTime::currentTime().toString();

    // По типу определяем, к какому уровню относится сообщение
    switch (type)
    {
    case QtInfoMsg:     out << " INFO\t"; break;
    case QtDebugMsg:    out << " DEBUG\t"; break;
    case QtWarningMsg:  out << " WARNING"; break;
    case QtCriticalMsg: out << " CRITICAL\n"; break;
    case QtFatalMsg:    out << " FATAL\n";
    }

    #ifdef QT_DEBUG
    // в режиме DEBUG перед сообщением пишем название функции
    out << ": " << context.function;
    qDebug() << context.function << "  : "  << msg; // дублируем в консоль
    #endif

    // записываем сообщение
    out << msg << endl;

    out.flush();    // Очищаем буферизированные данные
    logFile.close();
}
