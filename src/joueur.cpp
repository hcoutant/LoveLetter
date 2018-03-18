#include "joueur.h"

Joueur::Joueur(std::string nm)
{
	nom = nm;
	en_vie = false;
	est_protege = false;
	c1 = nullptr;
	c2 = nullptr;
}

Joueur::~Joueur() {}

void Joueur::ajouter_jeu(Jeu* je) {} //TODO!!
