#include <iostream>
#include "jeu.h"


int main(void)
{
	Joueur *j1 = new Joueur("Jean");
	Joueur *j2 = new Joueur("Robert");

	Jeu *j = new Jeu(j1,j2);
	
	j1->ajouter_jeu(j);
	j2->ajouter_jeu(j);

	j->initialisation();
	
	std::cout << j1->getCarteMg()->getType() << std::endl;

	std::cout << j2->getCarteMg()->getType() << std::endl;

	return 0;
}
