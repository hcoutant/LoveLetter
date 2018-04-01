#include "joueur.h"

Joueur::Joueur(std::string nm)
{
	nom = nm;
	en_vie = false;
	est_protege = false;
	c1 = nullptr;
	c2 = nullptr;
	j = nullptr;
	score = 0;
}

Joueur::~Joueur() {}

void Joueur::ajouterJeu(Jeu* je) 
{
	j = je;
} 

int Joueur::jouerCarteMg(Joueur *jo) 
{
	retour ret;
	if(c1->getType() == PRETRE)
	{
		Carte* ca = new Pretre();
		ret = j->action(this,jo,ca);
		//Dans ca on aura la carte de l'autre joueur
	}
	else
		ret = j->action(this,jo,c1);
	
	if(ret == OK)
	{
		if(this->estVivant())
		{
			j->defausser(c1);
			c1 = nullptr;
		}
	}
	
	return ret;
}

int Joueur::jouerCarteMd(Joueur *jo)
{
	retour ret;
	if(c2->getType() == PRETRE)
	{
		Carte* ca = new Pretre();
		ret = j->action(this,jo,ca);
	}
	else
		ret = j->action(this,jo,c2);
	
	if(ret ==  OK)
	{
		if(this->estVivant())
		{
			j->defausser(c2);
			c2 = nullptr;
		}
	}
	
	return ret;
}

int Joueur::jouerCarteMg(Joueur *jo, Carte* c)
{
	retour ret = j->action(this,jo,c1,c);
	if(this->estVivant())
	{
		j->defausser(c1);
		c1 = nullptr;
	}
	return ret;
}

int Joueur::jouerCarteMd(Joueur *jo, Carte* c)
{
	retour ret = j->action(this,jo,c2,c);
        if(this->estVivant())
        {
                j->defausser(c2);
                c2 = nullptr;
        }
        return ret;
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
		if(c1->getType() == PRINCESSE)
                        this->setVivant(false);
		c1 = nullptr;
	}
	else
	{
		j->defausser(c2); 
		if(c2->getType() == PRINCESSE)
			this->setVivant(false);
		c2 = nullptr;
	}
}

void Joueur::piocher()
{
	Carte* ca = j->piocher();
	if(c1 == nullptr)
		this->setCarteMg(ca);
	else
		this->setCarteMd(ca);
}

std::string Joueur::getNom()
{
	return nom;
}
