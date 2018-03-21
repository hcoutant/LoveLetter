#include "jeu.h"

Jeu::Jeu(Joueur* j1, Joueur* j2, Joueur* j3, Joueur* j4)
{	
	assert(j1 != nullptr && j2 != nullptr);
	joueurs.push_back(j1);
	joueurs.push_back(j2);

	if(j3 != nullptr)
		joueurs.push_back(j3);
	if(j4 != nullptr)
		joueurs.push_back(j4);



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
}

void Jeu::action(Joueur *j1, Joueur *j2, Carte* c)
{
	/*Il faudrait retourner un enum en fonction du type d'erreur 
	  Si le joueur n'est pas vivant, retourner NOT_ALIVE
	  Si le joueur est protégé, renvoyer PROTEGE etc ... */
	if(j1 != j2 && j2->estProtege())
		return;

	if(!(j2->estVivant()))
		return;
	

	switch(c->getType()){ }
}
