#ifndef __BARON_H__
#define __BARON_H__

#include "../../jeu.h"
#include "../carte.h"

class Baron : Carte {
        public:
                Baron();
                ~Baron();
                void action(Jeu* j, Joueur* jo);
};

#endif
