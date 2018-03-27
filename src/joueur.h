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
		
		//int, pas retour parce que ... le c++ \o/
		int jouerCarteMg(Joueur* jo);
		int jouerCarteMd(Joueur* jo);

		bool estVivant();
		void setVivant(bool b);
	
		bool estProtege();
		void setProtege(bool b);
		
		Carte* getCarteMg();
		void setCarteMg(Carte* c);

		Carte* getCarteMd();
		void setCarteMd(Carte* c);

		void defausser();
		void piocher();
};

#endif
