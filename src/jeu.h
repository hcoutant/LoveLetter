#ifndef __JEU_H__
#define __JEU_H__

#include <vector>

#include "carte.h"
#include "joueur.h"

class Jeu {
	private:
		std::vector<Carte*> pile; //Pas de stack (Car impossible de mélanger une stack)
		std::vector<Joueur*> joueurs;
		std::vector<Carte*> defausse; //Cartes qui ont été défaussées par les joueurs (Ou mis dedans au début du jeu)
	public:
		Jeu(Joueur* j1, Joueur* j2, Joueur *j3 = nullptr, Joueur *j4 = nullptr);
		~Jeu();
};

#endif
