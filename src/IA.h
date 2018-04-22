#ifndef IA_H__
#define IA_H__
#include <string>
#include <cstdlib>
#include <ctime>
#include "joueur.h"
#include "carte.h"

class Ia : public Joueur    {
    public:
      Ia();

	// fonctions pour choisir la carte à jouer
    Carte* jouerBaron();
    Carte* jouerComtesse ();
    Carte* jouerPrincesse();
	// chacune des 3 fonctions précédente traite le cas particulier où la princesse/comtesse/baron est parmi les deux cartes se trouvant en main de l'IA.

    Carte* jouerCarte();
     /* cette fonction sera passé en param
    de la fonction Jeu::action afin de remplacer le param de la carte qui sera jouer.
        Elle renvoie la carte choisie  */

	// fonctions pour cibler un joueur

Joueur* ciblerAleatoirement();
	// fonction qui cible un joueur aléatoirement parmi ceux encore dans la partie

Joueur* ciblerEnAyantRoi(Carte* carteChoisie);
	// fonction qui cible un joueur dans le cas où la carte jouée est le roi.

Joueur* ciblerEnAyantPrince(Carte* carteChoisie);
	// fonction qui cible un joueur dans le cas où la carte jouée est un prince

Joueur* ciblerJoueur(Carte* carteChoisie);
	// fonction qui renvoie le joueur ciblé.

};
#endif
