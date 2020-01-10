
QT += core gui widgets


# вспомогательные классы
include( ../toolkit/tklog/TKlog.pri )

TEMPLATE = app

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        tmp/testjson.cpp

HEADERS += \
        mainwindow.h \
        tmp/testjson.h


CONFIG(release, debug|release): DEFINES += QT_NO_DEBUG_OUTPUT
