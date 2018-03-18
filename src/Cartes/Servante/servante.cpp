#include "servante.h"

Servante::Servante()
{
	nom = "Servante";
	description = "Jusqu'au prochain tour, vous êtes protégé des effets des cartes des autres joueurs.";
	valeur = 4;
}

Servante::~Servante(){}

void Servante::action(Jeu* j, Joueur *jo) {} //TODO
