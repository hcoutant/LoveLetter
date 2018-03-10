#ifndef __CARTE_H__
#define __CARTE_H__

#include <string>

class Carte {
	private:
		std::string nom;
		int valeur;
	public:
		Carte(std::string nom, int valeur);
		~Carte();
};

#endif // !__CARTE_H__
