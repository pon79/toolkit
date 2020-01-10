
QT += core gui widgets


# вспомогательные классы
include( ../toolkit/tklog/TKlog.pri )

TEMPLATE = app

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h


CONFIG(release, debug|release): DEFINES += QT_NO_DEBUG_OUTPUT


DISTFILES += \
    tklog/TKlog.pri
