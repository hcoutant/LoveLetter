#include <iostream>
#include <limits>

int main(void)
{
	std::cout << "Bienvenue dans la version en ligne de commande de Love Letter !" << std::endl;
	std::cout << std::endl;

	std::cout << "Combien de joueurs ?" << std::endl;

	int nb_joueurs;
	
	std::cin >> nb_joueurs;

	
	while(nb_joueurs > 4 || nb_joueurs < 2 || std::cin.fail())
	{

		
		std::cout << "Choisissez un nombre de joueurs entre 2 et 4 !" << std::endl;
	
		std::cin.clear(); 
	     	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cin >> nb_joueurs;
	}
	
	std::cout << "Jeu à " << nb_joueurs << std::endl;
	return 0;
}
