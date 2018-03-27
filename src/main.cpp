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
	

	j1->setCarteMg(new Baron());
	j1->setCarteMd(new Garde());

	std::cout << "Joueur 1" << std::endl;
	std::cout << j1->getCarteMg()->affiche() << std::endl;
	std::cout << j1->getCarteMd()->affiche() << std::endl;


	std::cout << std::endl << "Joueur 2" << std::endl;
	std::cout << j2->getCarteMg()->affiche() << std::endl;

	
	j1->jouerCarteMg(j2);

	std::cout << std::endl << "Joueur 1" << std::endl;
	
	if(j1->getCarteMg() != nullptr)
	        std::cout << j1->getCarteMg()->affiche() << std::endl;
	if(j1->getCarteMd() != nullptr)
		std::cout << j1->getCarteMd()->affiche() << std::endl;


	


	  std::cout << std::endl << "Joueur 2" << std::endl;


	if(j2->getCarteMg() != nullptr)
                std::cout << j2->getCarteMg()->affiche() << std::endl;
        if(j2->getCarteMd() != nullptr)
                std::cout << j2->getCarteMd()->affiche() << std::endl;



	return 0;
}
