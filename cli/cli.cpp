#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "../src/joueur.h"

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
	
	std::cout << "Jeu à " << nb_joueurs << std::endl << std::endl;

	std::vector<Joueur*> joueurs;

	std::string s;
	for(int i = 0 ; i < nb_joueurs ; i++)
	{
		std::cout << "Joueur " << i+1 << ", entrez votre nom" << std::endl;
		std::cin >> s;
		joueurs.push_back(new Joueur(s));
	}

	std::cout << std::endl;

	Jeu *j = new Jeu(joueurs);

	for(int i = 0 ; i < nb_joueurs ; i++)
		joueurs[i]->ajouterJeu(j);


	j->initialisation();

	Joueur* gagnant;

	while(!(gagnant = j->finis()))
	{
		std::vector<Joueur*> ggManches;
		while((ggManches = j->mancheFinis()).size() == 0 || j->jeuMort())
		{
			for(unsigned int i = 0 ; i < joueurs.size() ; i++)
			{
				if(!joueurs[i]->estVivant())
					continue;
				
				bool b = false;
				for(Joueur* jr : joueurs)
				{
					if(jr == joueurs[i])
						continue;
					if(jr->estVivant())
						b = true;
				}
				
				if(!b)
					continue; //On est le seul joueur vivant on ne pioche plus
				
				joueurs[i]->setProtege(false);

				joueurs[i]->piocher();
				std::cout << "Joueur " << joueurs[i]->getNom() << " voici vos cartes" << std::endl;
				std::cout << "Main gauche : " << joueurs[i]->getCarteMg()->affiche() << std::endl;
				std::cout << "Main droite : " << joueurs[i]->getCarteMd()->affiche() << std::endl;

			lab_action:
				std::cout << "Que décidez-vous de jouer ? (g pour gauche, d pour droite, droit par défaut" << std::endl;
				
				char c;
				std::cin >> c;
				int r;
				
				Joueur* cible = nullptr; 

				if(c == 'g')
				{
					type_carte t = joueurs[i]->getCarteMg()->getType();
					if(t == PRINCESSE || t == COMTESSE || t == SERVANTE)
						r = joueurs[i]->jouerCarteMg(joueurs[i]);
					else
					{
					lab_cible:
						std::cout << "Vous devez choisir le numéro du joueur cible" << std::endl;
						unsigned int j;
						std::cin >> j;
						if(j > joueurs.size())
						{
							std::cout << "Vous devez choisir un nombre valide !" << std::endl; 
							goto lab_cible;
						}						
						cible = joueurs[j-1];
						if(t == GARDE)
						{
						label_ga1:
							std::cout << "Veuillez entrer le nom de la carte que vous voulez deviner" << std::endl;
							std::string s;
							std::cin >> s;

							Carte* c = Carte::getTypeFromString(s);
							if(c == nullptr)
							{
								std::cout << "Cette carte n'existe pas" << std::endl;
								goto label_ga1;
							}

							r = joueurs[i]->jouerCarteMg(cible,c);
						}
						else
							r = joueurs[i]->jouerCarteMg(cible);
					}

				}
				else
				{
					type_carte t = joueurs[i]->getCarteMd()->getType();
					if(t == PRINCESSE || t == COMTESSE || t == SERVANTE)
						r = joueurs[i]->jouerCarteMd(joueurs[i]);
					else
                                        {
                                        lab_cible2:
                                                std::cout << "Vous devez choisir le numéro du joueur cible" << std::endl;
                                                unsigned int j;
                                                std::cin >> j;
                                                if(j > joueurs.size())
                                                {
                                                        std::cout << "Vous devez choisir un nombre valide !" << std::endl;
                                                        goto lab_cible2;
                                                }
						cible = joueurs[j-1];
						if(t == GARDE)
                                                {
                                                label_ga2:
                                                        std::cout << "Veuillez entrer le nom de la carte que vous voulez deviner" << std::endl;
                                                        std::string s;
                                                        std::cin >> s;

                                                        Carte* c = Carte::getTypeFromString(s);
                                                        if(c == nullptr)
                                                        {
                                                                std::cout << "Cette carte n'existe pas" << std::endl;
                                                                goto label_ga2;
                                                        }

                                                        r = joueurs[i]->jouerCarteMd(cible,c);
                                                }
						else
                                                	r = joueurs[i]->jouerCarteMd(cible);
                                        }
				}
				if(r != OK)
				{
					if(r == DEAD)
						std::cout << "Le joueur que vous ciblez n'est pas vivant !" << std::endl;
					else if(r == COMT)
						std::cout << "Vous devez jouer la comptesse !" << std::endl;
					else 
						std::cout << "Le joueur que vous ciblez est protégé !" << std::endl;
					goto lab_action;
				}

				if(cible != nullptr && !(cible->estVivant()))
					std::cout << "Le joueur " << cible->getNom() << " est éliminé de la manche" << std::endl;
				else if(!(joueurs[i]->estVivant()))
					std::cout << "Le joueur " << joueurs[i]->getNom() << " est éliminé de la manche" << std::endl;



			}
			

		}

		

		if(ggManches.size() == 0)
			std::cout << "Aucun joueur n'a remporté la manche" << std::endl;
		else if(ggManches.size() == 1)
			std::cout << "Le joueur " << ggManches[0]->getNom() << " remporte la manche" << std::endl;
		else
		{
			std::cout << "Les joueurs ";
			for(Joueur* jo : ggManches)
				std::cout << jo->getNom() << " ";

			std::cout << " ont gagnés la manche" << std::endl;
		}


		j->refresh(ggManches);

		std::cout << std::endl << "Récapitulatif du score" << std::endl;
                for(Joueur *jr : joueurs)
                        std::cout << "Joueur " << jr->getNom() << " possède " << jr->getScore() << "points" << std::endl;
	}

	std::cout << "Le joueur " << gagnant->getNom() << " a gagné la partie !" << std::endl;

	return 0;
}
