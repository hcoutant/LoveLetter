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
		defausse.push_back(pile.back());
		defausse.pop_back();
	}
	else
	{
		defausse.push_back(pile.back());
		defausse.pop_back();
		defausse.push_back(pile.back());
                defausse.pop_back();
		defausse.push_back(pile.back());
                defausse.pop_back();
		defausse.push_back(pile.back());
                defausse.pop_back();
	}
}
