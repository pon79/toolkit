QT += core gui widgets xml network

# вспомогательные классы
include( ../toolkit/tklog/TKlog.pri )

TEMPLATE = app

SOURCES += \
        tmp/testjson.cpp \
        mainwindow.cpp \
        main.cpp \
        tmp/udprequest.cpp \
        tmp/tmpnetwork.cpp

HEADERS += \
        tmp/testjson.h \
        mainwindow.h \
        tmp/udprequest.h \
        tmp/tmpnetwork.h

# use_XML
QT += xml
SOURCES += tmp/tmpxml.cpp tmp/onvif.cpp
HEADERS += tmp/tmpxml.h tmp/onvif.h


#CONFIG(release, debug|release): DEFINES += QT_NO_DEBUG_OUTPUT
