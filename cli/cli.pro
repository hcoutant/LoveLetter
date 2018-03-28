HEADERS += ../src/jeu.h ../src/joueur.h ../src/carte.h

SOURCES += cli.cpp ../src/jeu.cpp ../src/joueur.cpp ../src/carte.cpp

DESTDIR += ../bin

OBJECTS_DIR += ../obj

QMAKE_CXXFLAGS += -std=c++0x

QT -= gui core 

