#include "jeu.h"

Jeu::Jeu(std::vector<Joueur*> jrs)
{	
	assert(jrs.size() >= 2 && jrs.size() <= 4);

	for(unsigned int i = 0 ; i < jrs.size() ; i++)
		joueurs.push_back(jrs[i]);



	pile.push_back(new Princesse());
	pile.push_back(new Comtesse());
	pile.push_back(new Roi());
	pile.push_back(new Prince());
	pile.push_back(new Prince());
	pile.push_back(new Servante());
	pile.push_back(new Servante());
	pile.push_back(new Baron());
	pile.push_back(new Baron());
	pile.push_back(new Pretre());
	pile.push_back(new Pretre());
	pile.push_back(new Garde());
	pile.push_back(new Garde());
	pile.push_back(new Garde());
	pile.push_back(new Garde());
	pile.push_back(new Garde());

	std::srand(time(nullptr));
	std::random_shuffle(pile.begin(),pile.end());

	if(joueurs.size() > 2)
	{
		laisse.push_back(pile.back());
		pile.pop_back();
	}
	else
	{
		laisse.push_back(pile.back());
		pile.pop_back();
		laisse.push_back(pile.back());
                pile.pop_back();
		laisse.push_back(pile.back());
                pile.pop_back();
		laisse.push_back(pile.back());
                pile.pop_back();
	}

	tour = 0;
}

retour Jeu::action(Joueur *j1, Joueur *j2, Carte*& c)
{
	/*Il faudrait retourner un enum en fonction du type d'erreur 
	  Si le joueur n'est pas vivant, retourner NOT_ALIVE
	  Si le joueur est protégé, renvoyer PROTEGE etc ... */

	if(!(j1->estVivant()))
		return DEAD;

	switch(c->getType()){ 
		case PRINCESSE: //Suicide
			j1->setVivant(false);
			break;
		case ROI: //Swap de carte
		{
			if(j1 != j2 && !(j2->estVivant()))
				return DEAD;
			if(j1 != j2 && j2->estProtege())
				return PROT;
	
			if(j1->getCarteMg()->getType() == COMTESSE || j1->getCarteMd()->getType() == COMTESSE)
				return COMT;

			bool b1 = j1->getCarteMg()->getType() == ROI;
			bool b2 = j2->getCarteMg() == nullptr;
			Carte *tmp = b1 ? j1->getCarteMd() : j1->getCarteMg();
			Carte *cj2 = b2 ? j2->getCarteMd() : j2->getCarteMg();
			b1 ? j1->setCarteMd(cj2) : j1->setCarteMg(cj2); 
			b2 ? j2->setCarteMd(tmp) : j2->setCarteMg(tmp);
			break;
		}
		case PRINCE: //Defausser
		{
			if(j1 != j2 && !(j2->estVivant()))
                                return DEAD;
                        if(j1 != j2 && j2->estProtege())
                                return PROT;
	
			if(j1->getCarteMg()->getType() == COMTESSE || j1->getCarteMd()->getType() == COMTESSE)
                                return COMT;

		
			if(j1 != j2)
			{
				j2->defausser();
				if(!j2->estVivant())
					break;

				j2->piocher();
			}
			else
			{
				if(j1->getCarteMd()->getType() == PRINCE)
				{
					this->defausser(j1->getCarteMg());
					if(j1->getCarteMg()->getType() == PRINCESSE)
						j1->setVivant(false);
					j1->setCarteMg(nullptr);
				}
				else
				{
					this->defausser(j1->getCarteMd());
					if(j1->getCarteMd()->getType() == PRINCESSE)
						j1->setVivant(false);
					j1->setCarteMd(nullptr);
				}
				if(!j1->estVivant())
					break;
				j1->piocher();
			}
			break;
		}
		case SERVANTE: //Protection 
			j1->setProtege(true);
			break;
		case PRETRE: //Regarde une carte
		{
			if(j1 != j2 && !(j2->estVivant()))
                                return DEAD;
                        if(j1 != j2 && j2->estProtege())
                                return PROT;

			Carte* ca = j2->getCarteMd() ==nullptr ? j2->getCarteMg() : j2->getCarteMd();
			c = ca;
			break;	
		}
		case BARON: //Duel
		{
			if(j1 != j2 && !(j2->estVivant()))
                                return DEAD;
                        if(j1 != j2 && j2->estProtege())
                                return PROT;
			
			Carte* tmp1 = j1->getCarteMd()->getType() == BARON ? j1->getCarteMg() : j1->getCarteMd();
			Carte* tmp2 = j2->getCarteMd() == nullptr ? j2->getCarteMg() : j2->getCarteMd();
			
			if(tmp1->getValeur() == tmp2->getValeur())
				break;
			else if(tmp1->getValeur() > tmp2->getValeur())
				j2->setVivant(false);
			else
				j1->setVivant(false);
			
		
			break;
		}
		case COMTESSE: //Roi ou Prince en main
		{
			if(j1->getCarteMd()->getType() == COMTESSE)
			{
				this->defausser(j1->getCarteMd());
				j1->setCarteMd(nullptr);
			}
			else
			{
				this->defausser(j1->getCarteMg());
				j1->setCarteMg(nullptr);
			}
			break;
		}
		default:
			break;

	}
	return OK;
}

retour Jeu::action(Joueur *j1, Joueur *j2, Carte* c1, Carte* c2) //Pour Garde
{
	
	if(j1 != j2 && !(j2->estVivant()))
        	return DEAD;
        if(j1 != j2 && j2->estProtege())
        	return PROT;
	
	if(c1->getType() != GARDE)
		return DEAD;
	
	if(j2->getCarteMg() == nullptr)
	{
		if(j2->getCarteMd()->getType() == c2->getType())
		{
			this->defausser(j2->getCarteMd());
			j2->setCarteMd(nullptr);
			j2->setVivant(false);
		}
	}
	else
	{
		if(j2->getCarteMg()->getType() == c2->getType())
                {
                        this->defausser(j2->getCarteMg());
                        j2->setCarteMg(nullptr);
                        j2->setVivant(false);
                }

	}
	
	return OK;
}


Carte* Jeu::piocher()
{
	if(pile.size() == 0)
		return nullptr;

	Carte* tmp = pile.back();
	pile.pop_back();
	return tmp;
}

Carte* Jeu::piocherLaisse()
{
	Carte* tmp = laisse.back();
	laisse.pop_back();
	return tmp;
}

void Jeu::defausser(Carte* c)
{
	defausse.push_back(c);
}

void Jeu::initialisation()
{
	for(unsigned int i = 0 ; i < joueurs.size() ; i++)
	{
		joueurs[i]->setVivant(true);
		joueurs[i]->piocher();
	}
}

bool Jeu::finis()
{
	int en_vie = 0;
	for(unsigned int i = 0; i < joueurs.size() ; i++)
		if(joueurs[i]->estVivant())
			en_vie++;

	return pile.size() == 0 || en_vie == 1;
}
	
void Jeu::nextTour() {
	
	do{
	tour += 1;
	tour = tour % joueurs.size();
	} while(!joueurs[tour]->estVivant());

}

int Jeu::nbPointGagner()
{
	if(joueurs.size() == 2)
		return 7;
	else if(joueurs.size() == 3)
		return 5;
	else
		return 4;
}
