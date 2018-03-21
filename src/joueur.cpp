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

void Joueur::ajouter_jeu(Jeu* je) 
{
	j = je;
} 

void Joueur::jouer_carte_mg(Joueur *jo) 
{
	j->action(this,jo,c1);
}

void Joueur::jouer_carte_md(Joueur *jo)
{
	j->action(this,jo,c2);
}

bool Joueur::estVivant()
{
	return en_vie;
}

bool Joueur::estProtege()
{
	return est_protege;
}


