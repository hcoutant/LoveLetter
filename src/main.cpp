#include <iostream>
#include "jeu.h"


int main(void)
{
	Joueur *j1 = new Joueur("Jean");
	Joueur *j2 = new Joueur("Robert");

	Jeu *j = new Jeu(j1,j2);
	
	j1->ajouter_jeu(j);
	j2->ajouter_jeu(j);

	

	return 0;
}
