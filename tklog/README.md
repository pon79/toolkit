# Логирование в Qt проектах.

Log files are written to the user settings directory (example /home/user/.config).
In the folder with the name of the company + the name of the program.


```c++
#include "mainwindow.h"
#include <QApplication>

#ifdef use_TKlog
#include "tklog.h"
#endif

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	#ifdef use_TKlog
	qInstallMessageHandler(ToolKit::Log::messageHandler);
	#endif

	MainWindow w;
	w.show();

	return a.exec();
}
```

[Warning and Debugging Messages](https://doc.qt.io/qt-5/debug.html#warning-and-debugging-messages):

Qt includes global macros for writing out warning and debug text. You can use them for the following purposes:

    qDebug() is used for writing custom debug output.
    qInfo() is used for informational messages.
    qWarning() is used to report warnings and recoverable errors in your application.
    qCritical() is used for writing critical error messages and reporting system errors.
    qFatal() is used for writing fatal error messages shortly before exiting.

Example:
```c++
if ( logDir.mkpath( logDir.path() ) )
    qInfo() << "created logging directory";
else
    qWarning() << "failed to create logging directory";
```
