Вспомогательные классы для Qt проектов
 
[TKlog](https://github.com/pon79/toolkit/tree/master/tklog) - логирование в Qt проектах.

Для использования нужно добавить в проектный файл приложения файл TKlog.pri
Например:

	QT       += core gui widgets

	TEMPLATE = app

	# вспомогательные классы
	include( ../toolkit/tklog/TKlog.pri )

	CONFIG += c++17

	SOURCES += \
		  main.cpp \
		  mainwindow.cpp

	HEADERS += \
		  mainwindow.h
