# Вспомогательные классы для Qt проектов
 
[TKlog](https://github.com/pon79/toolkit/tree/master/tklog) - logger.

[xmlToJson](https://github.com/pon79/toolkit/tree/master/xmlToJson) - XML to JSON converter

Example:

	QT       += core gui widgets

	TEMPLATE = app
	
	include( ../toolkit/tklog/TKlog.pri )
	include( ../toolkit/xmlToJson/xmlToJson.pri )

	CONFIG += c++17

	SOURCES += \
		  main.cpp \
		  mainwindow.cpp

	HEADERS += \
		  mainwindow.h
