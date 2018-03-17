#ifndef __CARTE_H__
#define __CARTE_H__

#include <string>

class Carte {
	private:
		std::string nom;
		std::string description;
		int valeur;
	public:
		Carte(std::string nom, int valeur, std::string description);
		~Carte();
};

#endif
