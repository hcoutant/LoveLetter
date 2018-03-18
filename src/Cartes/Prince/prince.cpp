#include "prince.h"

Prince::Prince()
{
	nom = "Prince";
	description = "Choisissez un joueur (y compris vous), celui-ci défausse la carte qu'il a en main \
			pour en piocher une nouvelle.";
	valeur = 5;
}

Prince::~Prince(){}

void Prince::action(Jeu* j, Joueur* jo) {} //TODO
