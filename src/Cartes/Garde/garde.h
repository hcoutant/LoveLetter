#ifndef __GARDE_H__
#define __GARDE_H__

#include "../carte.h"

class Garde : Carte {
        public:
                Garde();
                ~Garde();
                void action(Jeu* j, Joueur* jo);
};

#endif
