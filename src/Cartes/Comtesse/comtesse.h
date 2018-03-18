#ifndef __COMPTESSE_H__
#define __COMPTESSE_H__

#include "../carte.h"


class Comtesse : Carte {
        public:
                Comtesse();
                ~Comtesse();
                void action(Jeu* j, Joueur* jo);
};

#endif
