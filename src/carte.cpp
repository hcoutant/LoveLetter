#include "carte.h"

Baron::Baron()
{
        nom = "Baron";
        description = "Comparez votre carte avec celle d'un autre joueur, celui qui a la carte \
                        avec la plus faible valeur est éliminé de la manche.";
        valeur = 3;
}

Baron::~Baron() {}

void Baron::action(Jeu* j, Joueur *jo) {} //TODO


Prince::Prince()
{
        nom = "Prince";
        description = "Choisissez un joueur (y compris vous), celui-ci défausse la carte qu'il a en main \
                        pour en piocher une nouvelle.";
        valeur = 5;
}

Prince::~Prince(){}

void Prince::action(Jeu* j, Joueur* jo) {} //TODO


Roi::Roi()
{
        nom = "Roi";
        description = "Echangez votre main avec un autre joueur de votre choix.";
        valeur = 6;
}

Roi::~Roi() {}

void Roi::action(Jeu* j, Joueur *jo) {} //TODO

Servante::Servante()
{
        nom = "Servante";
        description = "Jusqu'au prochain tour, vous êtes protégé des effets des cartes des autres joueurs.";
        valeur = 4;
}

Servante::~Servante(){}

void Servante::action(Jeu* j, Joueur *jo) {} //TODO


Comtesse::Comtesse()
{
        nom = "Comtesse";
        description = "Si vous avez cette carte en main en même temps que le Roi ou le Prince, alors \
                        vous devez défausser la carte de la Comtesse";
        valeur = 7;
}

Comtesse::~Comtesse() {}

void Comtesse::action(Jeu* j, Joueur *jo) {} //TODO

Garde::Garde()
{
        nom = "Garde";
        description = "Choisissez un joueur et essayer de deviner la carte qu'il a en main (excepté le garde), \
                        si vous tombez juste, le joueur est éliminé de la manche.";
        valeur = 1;
}

Garde::~Garde() {}

void Garde::action(Jeu* j, Joueur *jo) {} //TODO

Princesse::Princesse()
{
        nom = "Princesse";
        description = "Si vous défaussez cette carte, vous êtes éliminé de la manche.";
        valeur = 8;
}

Princesse::~Princesse() {}

void Princesse::action(Jeu* j, Joueur *jo) {} //TODO


Pretre::Pretre()
{
        nom = "Pretre";
        description = "Regardez la main d'un autre joueur.";
        valeur = 2;
}

Pretre::~Pretre() {}

void Pretre::action(Jeu* j, Joueur *jo) {} //TODO
