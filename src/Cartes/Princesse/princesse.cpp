#include "princesse.h"


Princesse::Princesse()
{
	nom = "Princesse";
	description = "Si vous défaussez cette carte, vous êtes éliminé de la manche.";
	valeur = 8;
}

Princesse::~Princesse() {}

void Princesse::action(Jeu* j, Joueur *jo) {} //TODO
