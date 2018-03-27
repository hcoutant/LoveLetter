#ifndef JEU_H__
#define JEU_H__

#include <vector>
#include <cassert>
#include <algorithm>
#include <ctime>

#include "carte.h"
#include "joueur.h"

class Joueur;

class Jeu {
	private:
		std::vector<Carte*> pile; //Pas de stack (Car impossible de mélanger une stack)
		std::vector<Joueur*> joueurs;
		std::vector<Carte*> defausse; //Cartes qui ont été défaussées par les joueurs 
		std::vector<Carte*> laisse; //Cartes laissés au début du jeu

		int tour; //Donne le joueur qui doit jouer 
	public:
		Jeu(Joueur* j1, Joueur* j2, Joueur *j3 = nullptr, Joueur *j4 = nullptr);
		~Jeu();
		void action(Joueur *j1, Joueur *j2, Carte*& c); //Le joueur j1 est l'appelant, j2 le joueur visé
		Carte* piocher();
		Carte* piocherLaisse();
		void defausser(Carte* c);

		void initialisation();
		bool finis(); //Retourne vrai si le jeu est finis
	
};

#endif
