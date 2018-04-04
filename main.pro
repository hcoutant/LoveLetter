HEADERS += src/jeu.h src/joueur.h src/carte.h src/Serveur.h src/Client.h src/ThreadModifie.h

SOURCES += src/main.cpp src/jeu.cpp src/joueur.cpp src/carte.cpp src/Serveur.cpp src/Client.cpp src/ThreadModifie.cpp

DESTDIR += bin/

OBJECTS_DIR += obj/

QMAKE_CXXFLAGS += -std=c++0x
