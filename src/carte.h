#ifndef CARTE_H__
#define CARTE_H__

#include <string>

#include "jeu.h"
#include "joueur.h"

class Carte {
	protected:
		std::string nom;
		std::string description;
		int valeur;
	public:
		virtual void action(Jeu* j, Joueur* jo) = 0; //Methode abstract
};

class Baron : public Carte {
        public:
                Baron();
                ~Baron();
                void action(Jeu* j, Joueur* jo);
};

class Prince : public Carte {
        public:
                Prince();
                ~Prince();
                void action(Jeu* j, Joueur* jo);
};

class Roi : public Carte {
        public:
                Roi();
                ~Roi();
                void action(Jeu* j, Joueur* jo);

};

class Servante : public Carte {
        public:
                Servante();
                ~Servante();
                void action(Jeu* j, Joueur* jo);
};


class Comtesse : public Carte {
        public:
                Comtesse();
                ~Comtesse();
                void action(Jeu* j, Joueur* jo);
};

class Garde : public Carte {
        public:
                Garde();
                ~Garde();
                void action(Jeu* j, Joueur* jo);
};

class Princesse : public Carte {
        public:
                Princesse();
                ~Princesse();
                void action(Jeu* j, Joueur* jo);
};

class Pretre : public Carte {
        public:
                Pretre();
                ~Pretre();
                void action(Jeu* j, Joueur* jo);
};

#endif
