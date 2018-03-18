#include "roi.h"

Roi::Roi()
{
	nom = "Roi";
	description = "Echangez votre main avec un autre joueur de votre choix.";
	valeur = 6;
}

Roi::~Roi() {}

void Roi::action(Jeu* j, Joueur *jo) {} //TODO

