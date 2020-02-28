
QT += core gui widgets xml


# вспомогательные классы
include( ../toolkit/tklog/TKlog.pri )

TEMPLATE = app

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        tmp/onvif.cpp \
        tmp/testjson.cpp \
        tmp/tmpxml.cpp

HEADERS += \
        mainwindow.h \
        tmp/onvif.h \
        tmp/testjson.h \
        tmp/tmpxml.h


CONFIG(release, debug|release): DEFINES += QT_NO_DEBUG_OUTPUT
