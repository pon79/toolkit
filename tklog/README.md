Логирование в Qt проектах.

В режиме release записывает в файл события по уровням qInfo, qWarning, qCritical и qFatal.
В режиме debug добавляется вывод qDebug и сообщения дублируются в консоль.

Файл логирования пишется в каталоге с названием программы в домашней папке.

Пример использования:

```c++
#include "mainwindow.h"
#include <QApplication>

// вспомогательный класс для логирования
#include "tklog.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// Устанавливаем обработчик
	qInstallMessageHandler(TKlog::messageHandler);

	MainWindow w;
	w.show();

	return a.exec();
}
```
Далее внтури кода используем [Warning and Debugging Messages](https://doc.qt.io/qt-5/debug.html#warning-and-debugging-messages):

Qt includes global macros for writing out warning and debug text. You can use them for the following purposes:

    qDebug() is used for writing custom debug output.
    qInfo() is used for informational messages.
    qWarning() is used to report warnings and recoverable errors in your application.
    qCritical() is used for writing critical error messages and reporting system errors.
    qFatal() is used for writing fatal error messages shortly before exiting.

Например:
```c++
if ( logDir.mkpath( logDir.path() ) )
    qInfo() << "created logging directory";
else
    qWarning() << "failed to create logging directory";
```
