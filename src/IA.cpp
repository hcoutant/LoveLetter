#include "Ia.h"

Ia::Ia()    {}

    /* fonctions pour choisir une carte à jouer */

Carte* Ia::jouerBaron()    {
    if (c1->getType()== BARON)    {
      if (c2!=nullptr && c2->getValeur() >= 6)    {
        return c1;	// car vaut mieux jouer le baron quand on a une carte de grande valeur 
     }
    return c2;	// sinon, aucun intérêt à jouer le baron
    }
    if (c2->getType() == BARON)    {
      if (c1->getValeur() >= 6)    {
          return c2;	// pareil si on a le baron dans la main droite
      }
    return c1;
  }
}

Carte* Ia::jouerComtesse()    {
    if (c1->getType() == COMTESSE)    {
       if (c2->getType() == PRINCE || c2->getType()==ROI)    {
        return c1;	// obligé de choisir la comtesse dans ce cas.
    // Cette carte sera automatiquement défaussé une fois qu'elle est passée à Jeu::action.
      }
        return c2;	// dans le cas contraire, vaut mieux garder la comtesse et jouer une autre carte.
    }
    if (c2->getType() == COMTESSE)    {    // faire pareil pour la carte à droite
      if (c1->getType() == PRINCE || c1->getType()== ROI)    {
         return c2;
      }
      return c1;
    }
}

Carte* Ia::jouerPrincesse()    {
    if (c1->getType() == PRINCESSE)
        return c2;	// car l'IA ne doit en aucun cas choisir de jouer la princesse
    else if (c2->getType() == PRINCESSE)
        return c1;
}
    
Carte* Ia::jouerCarte()     {
    Carte* choisie;

    if (c1->getType() == c2->getType())
        choisie=c1;	// car l'IA a deux cartes identiques
    /* traitement des cas d'exception */
    if (c1->getType()==PRINCESSE || c2->getType()==PRINCESSE)
    choisie=Ia::jouerPrincesse();
    else if (c1->getType()==COMTESSE || c2->getType()==COMTESSE)
        choisie=Ia::jouerComtesse();
else if (c1->getType()==BARON || c2->getType()==BARON)
        choisie=Ia::jouerBaron();
    /* si aucun de ces cas ne s'applique alors */
      else if (c1->getValeur() < c2->getValeur())
      choisie=c1;	// vaut mieux jouer la carte dont la valeur est plus petite
    else choisie=c2;

  return choisie;
}

    /* fonctions pour cibler un joueur */

Joueur* Ia::ciblerAleatoirement()    {
    Joueur* joueurCible;
    int aleatoire, nbJoueurs;

    srand((unsigned)time(0));
    nbJoueurs=this->j->joueurs.size()-1;
    aleatoire= 0 + (int)((float)rand() * (nbJoueurs-0+1) / (RAND_MAX-1));
    joueurCible=this->j->joueurs[aleatoire];

  return joueurCible;
}

Joueur* Ia::ciblerEnAyantRoi(Carte* carteChoisie)    {
    Joueur* joueurCible;
    if (c1==carteChoisie)    {
        if (c2!=nullptr && c2->getValeur() >=4)    { // si la carte restante a une valeur >=4
             joueurCible=this;    // vaut mieux choisir de garder sa carte si sa valeur est élevée
        }
         joueurCible=Ia::ciblerAleatoirement();
   // sinon, choisir un joueur aléatoirement pour échanger sa carte avec lui.
  }
	// faire la même chose avec la carte à droite:
    if (c2==carteChoisie)    {
       if (c1!=nullptr && c1->getValeur() >=4)    {
        joueurCible=this;
      }
    else joueurCible=Ia::ciblerAleatoirement();
}
    return joueurCible;
}

Joueur* Ia::ciblerEnAyantPrince(Carte* carteChoisie)    {
    Joueur* joueurCible;
    if (c1==carteChoisie)    {
      if (c2!=nullptr && c2->getValeur() <4)    { // si on a une carte dont la valeur est <4
    // vaut mieux choisir de la deffausser afin d'en piocher une nouvelle pour augmenter la chance de tomber sur une carte plus puissante, et donc l'IA va se cibler elle-même.
        joueurCible=this;
      }
    else joueurCible=Ia::ciblerAleatoirement();
    }
  if (c2==carteChoisie)    {
       if (c1!=nullptr && c1->getValeur() <4)    { // pareil pour l'autre carte
        joueurCible=this;
    }
   else joueurCible=Ia::ciblerAleatoirement();
  }
return joueurCible;
}
 
Joueur* Ia::ciblerJoueur(Carte* carteChoisie)    {
    Joueur* joueurCible;

        if (carteChoisie->getType()==ROI)    {
        joueurCible=Ia::ciblerEnAyantRoi(carteChoisie);
    }
    else if (carteChoisie->getType()==PRINCE)    {
        joueurCible=Ia::ciblerEnAyantPrince(carteChoisie);
    }
    else if (carteChoisie->getType()==BARON || carteChoisie->getType()==PRETRE || carteChoisie->getType()==GARDE)    {
        joueurCible=Ia::ciblerAleatoirement();
    }

  return joueurCible;
}
