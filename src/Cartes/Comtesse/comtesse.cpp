#include "comtesse.h"

Comtesse::Comtesse()
{
	nom = "Comtesse";
	description = "Si vous avez cette carte en main en même temps que le Roi ou le Prince, alors \
			vous devez défausser la carte de la Comtesse";
	valeur = 7;
}

Comtesse::~Comtesse() {}

void Comtesse::action(Jeu* j, Joueur *jo) {} //TODO
