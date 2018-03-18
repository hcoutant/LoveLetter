#include "baron.h"

Baron::Baron()
{
	nom = "Baron";
	description = "Comparez votre carte avec celle d'un autre joueur, celui qui a la carte \
			avec la plus faible valeur est éliminé de la manche.";
	valeur = 3;
}

Baron::~Baron() {}

void Baron::action(Jeu* j, Joueur *jo) {} //TODO
