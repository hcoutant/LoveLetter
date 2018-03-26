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

void Joueur::jouerCarteMg(Joueur *jo) 
{
	j->action(this,jo,c1);
}

void Joueur::jouerCarteMd(Joueur *jo)
{
	j->action(this,jo,c2);
}

bool Joueur::estVivant()
{
	return en_vie;
}

void Joueur::setVivant(bool b)
{
	en_vie = b;
}

bool Joueur::estProtege()
{
	return est_protege;
}

void Joueur::setProtege(bool b)
{
	est_protege = b;
}

Carte* Joueur::getCarteMg()
{
	return c1;
}

void Joueur::setCarteMg(Carte* c)
{
	c1 = c;
}

Carte* Joueur::getCarteMd()
{
	return c2;
}

void Joueur::setCarteMd(Carte* c)
{
	c2 = c;
}
