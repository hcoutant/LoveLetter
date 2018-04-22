#ifndef CARTE_H__
#define CARTE_H__

#include <string>

//Typedef pour le type de cartes
typedef enum {
	BARON,
	PRINCE,
	ROI,
	SERVANTE,
	COMTESSE,
	GARDE,
	PRINCESSE,
	PRETRE
} type_carte;

class Carte {
	protected:
		std::string nom; //Nom de la carte
		std::string description; //Description de la carte (son action)
	        int valeur; //Valeur de la carte (Nombre de points qu'elle raporte)
		type_carte type; //Type de la carte (Princesse, Roi, ...)
	public:
		type_carte getType(); //Retourne le type de la carte
		int getValeur(); //Retourne la valeur de la carte
		std::string affiche(); //Retourne le nom de la carte sous la forme d'une chaine
		static Carte* getTypeFromString(std::string s); //Retourne un pointeur sur le carte de type s, si s ne correspond à aucun type retourne nullptr
};

class Baron : public Carte {
        public:
                Baron();
                ~Baron();
};

class Prince : public Carte {
        public:
                Prince();
                ~Prince();
};

class Roi : public Carte {
        public:
                Roi();
                ~Roi();
};

class Servante : public Carte {
        public:
                Servante();
                ~Servante();
};


class Comtesse : public Carte {
        public:
                Comtesse();
                ~Comtesse();
};

class Garde : public Carte {
        public:
                Garde();
                ~Garde();
};

class Princesse : public Carte {
        public:
                Princesse();
                ~Princesse();
};

class Pretre : public Carte {
        public:
                Pretre();
                ~Pretre();
};

#endif
