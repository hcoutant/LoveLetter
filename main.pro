HEADERS += src/jeu.h \
           src/joueur.h \
           src/Cartes/carte.h \
           src/Cartes/Baron/baron.h \
           src/Cartes/Comtesse/comtesse.h \
           src/Cartes/Garde/garde.h \
           src/Cartes/Pretre/pretre.h \
           src/Cartes/Prince/prince.h \
           src/Cartes/Princesse/princesse.h \
           src/Cartes/Roi/roi.h \
           src/Cartes/Servante/servante.h

SOURCES += src/jeu.cpp \
           src/main.cpp \
           src/Cartes/Baron/baron.cpp \
           src/Cartes/Comtesse/comtesse.cpp \
           src/Cartes/Garde/garde.cpp \
           src/Cartes/Pretre/pretre.cpp \
           src/Cartes/Prince/prince.cpp \
           src/Cartes/Princesse/princesse.cpp \
           src/Cartes/Roi/roi.cpp \
           src/Cartes/Servante/servante.cpp


DESTDIR += bin/

OBJECTS_DIR += obj/

QMAKE_CXXFLAGS += -std=c++0x
