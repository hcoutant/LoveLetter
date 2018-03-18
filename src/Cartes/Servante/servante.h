#ifndef __SERVANTE_H__
#define __SERVANTE_H__

#include "../../jeu.h"
#include "../carte.h"

class Servante : Carte {
        public:
                Servante();
                ~Servante();
                void action(Jeu* j, Joueur* jo);
};

#endif
