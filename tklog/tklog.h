/*!
 * Вспомогательный класс для логирования сообщений.
 *
 */

#ifndef TKLOG_H
#define TKLOG_H

#include <QLoggingCategory>
#include <QObject>

class TKlog
{

public:
    TKlog();

    /*!
     * Логирование в Qt проектах.
     * В режиме release записывает в файл события по уровням qInfo, qWarning, qCritical и qFatal.
     * В режиме debug добавляется вывод qDebug и сообщения дублируются в консоль.
     * Файл логирования пишется в каталоге с названием программы в домашней папке.
     * \param type Type: qInfo, qWarning, qCritical, qFatal, qDebug
     * \param context Provides additional information about a log message.
     * \param msg Message.
     */
    static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);


};

#endif // TKLOG_H
