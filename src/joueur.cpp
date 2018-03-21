#include "joueur.h"

Joueur::Joueur(std::string nm)
{
	nom = nm;
	en_vie = false;
	est_protege = false;
	c1 = nullptr;
	c2 = nullptr;
	j = nullptr;
}

Joueur::~Joueur() {}

void Joueur::ajouter_jeu(Jeu* je) {} //TODO!!

void Joueur::jouer_carte_mg(Joueur *jo) 
{
}

void Joueur::jouer_carte_md(Joueur *jo)
{
}


