#ifndef JOUEUR_H__
#define JOUEUR_H__

#include "jeu.h"

class Jeu; //Eviter les inclusions cyclique 



class Joueur {
	private:
		Jeu* j; //Jeu auquel le joueur est attaché
		bool en_vie; //Indique si le joueur est en vie
		bool est_protege; //Indique si le joueur est protégé
		std::string nom; //Indique le pseudo du joueur
		int score; //Indique le score du joueur

		Carte* c1; //La carte en main gauche du joueur
		Carte* c2; //La carte en main droite du joueur
	public:
		Joueur(std::string nom); //Constructeur 
		~Joueur(); //Destructeur
		void ajouterJeu(Jeu* j); //setter pour le jeu
		
		//int, pas retour parce que ... le c++ \o/
		int jouerCarteMg(Joueur* jo); //Joue la carte en main gauche
		int jouerCarteMd(Joueur* jo); //Joue la carte en main droite

		//Même chose que précédement, mais on garde un pointeur pour retourner ou passer une carte (Pretre et Garde)
		int jouerCarteMg(Joueur *jo, Carte* c); 
		int jouerCarteMd(Joueur *jo, Carte* c);

		bool estVivant(); //Getter pour savoir si un joueur est vivant
		void setVivant(bool b); //setter vivant
	
		bool estProtege(); //getter proteger
		void setProtege(bool b); //setter proteger
		
		Carte* getCarteMg(); //getter pour carte mg
		void setCarteMg(Carte* c); //setter pour carte mg

		Carte* getCarteMd(); //getter pour carte md
		void setCarteMd(Carte* c); //setter pour carte mg

		void defausser(); //Defausse ses cartes 
        	Carte* piocher(); //Pioche une carte

		std::string getNom(); //Retourne le pseudo du joueur
	
		int getScore(); //Getter pour le score
		void setScore(int); //Setter pour le score
};

#endif
