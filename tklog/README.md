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
