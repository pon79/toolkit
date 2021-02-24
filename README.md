# Вспомогательные классы для Qt проектов
 
[TKlog](https://github.com/pon79/toolkit/tree/master/tklog) - логирование.

[xmlToJson](https://github.com/pon79/toolkit/tree/master/xmlToJson) - конвертер из XML в JSON.

Для использования нужно добавить в проектный файл приложения файл .pri
Например:

	QT       += core gui widgets

	TEMPLATE = app

	# вспомогательные классы
	include( ../toolkit/tklog/TKlog.pri )
	include( ../toolkit/xmlToJson/xmlToJson.pri )

	CONFIG += c++17

	SOURCES += \
		  main.cpp \
		  mainwindow.cpp

	HEADERS += \
		  mainwindow.h
