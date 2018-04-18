QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bin/main
TEMPLATE = app


SOURCES += src/main.cpp src/mainwindow.cpp src/presentation.cpp src/callback.cpp src/jeu.cpp src/joueur.cpp src/carte.cpp

HEADERS  += src/mainwindow.h src/presentation.h src/callback.h src/jeu.h src/joueur.h src/carte.h

OBJECTS_DIR += obj/

FORMS    += src/mainwindow.ui

QMAKE_CXXFLAGS += -std=c++0x
