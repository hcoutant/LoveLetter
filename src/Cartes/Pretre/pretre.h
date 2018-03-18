#ifndef __PRETRE_H__
#define __PRETRE_H__

#include "../carte.h"

class Pretre : Carte {
        public:
                Pretre();
                ~Pretre();
                void action(Jeu* j, Joueur* jo);
};

#endif
