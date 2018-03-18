#ifndef __CARTE_H__
#define __CARTE_H__

#include <string>
#include "../jeu.h"
#include "../joueur.h"

class Carte {
	protected:
		std::string nom;
		std::string description;
		int valeur;
	public:
		virtual void action(Jeu* j, Joueur* jo) = 0; //Methode abstract
};

#endif
