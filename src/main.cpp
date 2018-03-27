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
	
	std::vector<Joueur*> joueurs;
	joueurs.push_back(j1);
	joueurs.push_back(j2);



	char rep;
	int i = 0;
	
	while(!j->finis())
	{
		joueurs[i%2]->setProtege(false);
		joueurs[i%2]->piocher();

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


		std::cin >> rep;

		if(rep == '1')
		{
			joueurs[i%2]->jouerCarteMg(joueurs[(i+1)%2]);
			std::cout << "Le joueur " << i%2 <<" joue sa carte en main gauche" << std::endl;
		}
		else
		{
			joueurs[i%2]->jouerCarteMd(joueurs[(i+1)%2]);
			std::cout << "Le joueur " << i%2<<" 1 joue sa carte en main droite" << std::endl;
		}

		j->nextTour();
		i++;
		std::cout << "_________________TOUR_SUIVANT_____________________" << std::endl;
	}

	return 0;
}
