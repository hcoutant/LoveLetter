#-------------------------------------------------
#
# Project created by QtCreator 2018-03-28T16:48:26
#
#-------------------------------------------------

QT       += core gui
QT        += printsupport
QT += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = interface_loveletter
TEMPLATE = app


SOURCES += main.cpp\
        fenetre.cpp \
    reglesjeu.cpp

HEADERS  += fenetre.h \
    reglesjeu.h

FORMS    += fenetre.ui \
    reglesjeu.ui
