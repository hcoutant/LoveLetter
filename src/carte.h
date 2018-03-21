#ifndef CARTE_H__
#define CARTE_H__

#include <string>

class Carte {
	protected:
		std::string nom;
		std::string description;
        int valeur;
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
