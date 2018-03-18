#include "garde.h"

Garde::Garde()
{
	nom = "Garde";
	description = "Choisissez un joueur et essayer de deviner la carte qu'il a en main (excepté le garde), \
			si vous tombez juste, le joueur est éliminé de la manche.";
	valeur = 1;
}

Garde::~Garde() {}

void Garde::action(Jeu* j, Joueur *jo) {} //TODO
