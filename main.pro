QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bin/main
TEMPLATE = app


SOURCES += src/main.cpp src/mainwindow.cpp src/presentation.cpp src/callback.cpp src/jeu.cpp src/joueur.cpp src/carte.cpp src/serveur.cpp src/client.cpp src/reglesjeu.cpp

HEADERS  += src/mainwindow.h src/presentation.h src/callback.h src/jeu.h src/joueur.h src/carte.h src/serveur.h src/client.h src/reglesjeu.h

OBJECTS_DIR += obj/

FORMS    += src/mainwindow.ui src/reglesjeu.ui

QMAKE_CXXFLAGS += -std=c++0x
