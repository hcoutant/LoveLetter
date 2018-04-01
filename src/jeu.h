#ifndef JEU_H__
#define JEU_H__

#include <vector>
#include <cassert>
#include <algorithm>
#include <ctime>

#include "carte.h"
#include "joueur.h"

typedef enum {
        OK, //Retourné par acion quand tout c'est bien passé :)
        PROT, //Retourné par action quand le joueur ciblé est protégé
        DEAD, //Retourné par action quand le joueur ciblé n'est plus actif
        COMT, //Retourné par action quand le joueur possède le roi/prince avec la comptesse en main
} retour;

class Joueur;



class Jeu {
	private:
		std::vector<Carte*> pile; //Pas de stack (Car impossible de mélanger une stack)
		std::vector<Joueur*> joueurs;
		std::vector<Carte*> defausse; //Cartes qui ont été défaussées par les joueurs 
		std::vector<Carte*> laisse; //Cartes laissés au début du jeu

		int tour; //Donne le joueur qui doit jouer 
	public:
		Jeu(std::vector<Joueur*>);
		~Jeu();
	
		retour action(Joueur *j1, Joueur *j2, Carte*& c); //Le joueur j1 est l'appelant, j2 le joueur visé
		retour action(Joueur *j1, Joueur *j2, Carte* c1, Carte* c2); //Pour Garde
	
		Carte* piocher();
		Carte* piocherLaisse();
		void defausser(Carte* c);

		void initialisation();
		bool finis(); //Retourne vrai si le jeu est finis

		void nextTour();

		int nbPointGagner(); //Retourne le nombre de points nécessaire pour gagner la partie
	
};

#endif
