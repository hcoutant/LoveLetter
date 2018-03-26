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
	if(c1->getType() == PRETRE)
	{
		Carte* ca = new Pretre();
		j->action(this,jo,ca);
		//Dans ca on aura la carte de l'autre joueur
	}
	else //Ne pas oublier le garde
		j->action(this,jo,c1);
}

void Joueur::jouerCarteMd(Joueur *jo)
{
	if(c2->getType() == PRETRE)
	{
		Carte* ca = new Pretre();
		j->action(this,jo,ca);
	}
	else
		j->action(this,jo,c2);
}

bool Joueur::estVivant()
{
	return en_vie;
}

void Joueur::setVivant(bool b)
{
	en_vie = b;
	if(!b)
	{
		if(c1 != nullptr)
		{
			j->defausser(c1);
			c1 = nullptr;
		}
		if(c2 != nullptr)
		{
			j->defausser(c2);
			c2 = nullptr;
		}
	}	
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

void Joueur::defausser()
{
	if(c1 != nullptr)
	{
		j->defausser(c1); 
		c1 = nullptr;
	}
	else
	{
		j->defausser(c2); 
		c2 = nullptr;
	}
}
