#ifndef __PRINCESSE_H__
#define __PRINCESSE_H__

#include "../carte.h"
#include "../../jeu.h"

class Princesse : Carte {
        public:
                Princesse();
                ~Princesse();
                void action(Jeu* j, Joueur* jo);
};

#endif
