#ifndef __PRINCE_H__
#define __PRINCE_H__

#include "../carte.h"

class Prince : Carte {
        public:
                Prince();
                ~Prince();
                void action(Jeu* j, Joueur* jo);
};

#endif
