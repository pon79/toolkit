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
