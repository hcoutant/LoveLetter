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
		std::vector<Joueur*> joueurs; //Vecteur des joueurs
		std::vector<Carte*> defausse; //Cartes qui ont été défaussées par les joueurs 
		std::vector<Carte*> laisse; //Cartes laissés au début du jeu
		int tour; //Donne le joueur qui doit jouer
	public:
		Jeu(std::vector<Joueur*>); //Constructeur
		~Jeu(); //Desctructeur
	
		retour action(Joueur *j1, Joueur *j2, Carte*& c); //Le joueur j1 est l'appelant, j2 le joueur visé
		retour action(Joueur *j1, Joueur *j2, Carte* c1, Carte* c2); //Pour Garde
	
		Carte* piocher(); //Pioche une carte dans la pile
		Carte* piocherLaisse(); //Pioche une carte dans les cartes laissées au début
		void defausser(Carte* c); //Defausse une carte

		void initialisation(); //Initialise le jeu
		
		Joueur* finis(); //Retourne le joueur qui a gagner la partie, nullptr si il n'y a pas encore de gagnant
		std::vector<Joueur*> mancheFinis(); //Retourne un vecteur de Joueurs gagnant de taille > à 0 si la manch est terminée
        	bool checkMancheFinis(); //Retourne vrai si la manche est finis
		bool jeuMort(); //Retourne vrai si tous les joueurs sont mort 
	
		void nextTour(); //Passe au prochain tour

		int nbPointGagner(); //Retourne le nombre de points nécessaire pour gagner la partie
		void refresh(std::vector<Joueur*>); //Donne les points aux gagants et reinitialise les cartes

	        int getNbCarte(); //Retourne le nombre de cartes restantes

		size_t nombreJoueur(); //Retourne le nombre de joueur
		Joueur* getJoueur(int i); //Retourne le ième joueur
};

#endif
