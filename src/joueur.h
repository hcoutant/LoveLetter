#ifndef JOUEUR_H__
#define JOUEUR_H__

#include "jeu.h"

class Jeu; //Eviter les inclusions cyclique 

class Joueur {
	private:
		Jeu* j;
		bool en_vie;
		bool est_protege;
		std::string nom;

		Carte* c1;
		Carte* c2;
	public:
		Joueur(std::string nom);
		~Joueur();
		void ajouter_jeu(Jeu* j);
		void jouer_carte_mg(Joueur* jo);
		void jouer_carte_md(Joueur* jo);
		bool estVivant();
		bool estProtege();
};

#endif
