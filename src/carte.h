#ifndef CARTE_H__
#define CARTE_H__

#include <string>

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
		std::string nom;
		std::string description;
	        int valeur;
		type_carte type;
	public:
		type_carte getType();
		int getValeur();
		std::string affiche();
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
