#ifndef __ROI_H__
#define __ROI_H__

#include "../carte.h"


class Roi : Carte {
        public:
                Roi();
                ~Roi();
                void action(Jeu* j, Joueur* jo);

};


#endif
