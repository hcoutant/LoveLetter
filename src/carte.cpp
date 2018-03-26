#include "carte.h"

type_carte Carte::getType()
{
	return type;
}

int Carte::getValeur()
{
	return valeur;
}

Baron::Baron()
{
        nom = "Baron";
        description = "Comparez votre carte avec celle d'un autre joueur, celui qui a la carte \
                        avec la plus faible valeur est éliminé de la manche.";
        valeur = 3;
	type = BARON;
}

Baron::~Baron() {}


Prince::Prince()
{
        nom = "Prince";
        description = "Choisissez un joueur (y compris vous), celui-ci défausse la carte qu'il a en main \
                        pour en piocher une nouvelle.";
        valeur = 5;
	type = PRINCE;
}

Prince::~Prince(){}



Roi::Roi()
{
        nom = "Roi";
        description = "Echangez votre main avec un autre joueur de votre choix.";
        valeur = 6;
	type = ROI;
}

Roi::~Roi() {}


Servante::Servante()
{
        nom = "Servante";
        description = "Jusqu'au prochain tour, vous êtes protégé des effets des cartes des autres joueurs.";
        valeur = 4;
	type = SERVANTE;
}

Servante::~Servante(){}


Comtesse::Comtesse()
{
        nom = "Comtesse";
        description = "Si vous avez cette carte en main en même temps que le Roi ou le Prince, alors \
                        vous devez défausser la carte de la Comtesse";
        valeur = 7;
	type = COMTESSE;
}

Comtesse::~Comtesse() {}


Garde::Garde()
{
        nom = "Garde";
        description = "Choisissez un joueur et essayer de deviner la carte qu'il a en main (excepté le garde), \
                        si vous tombez juste, le joueur est éliminé de la manche.";
        valeur = 1;
	type = GARDE;
}

Garde::~Garde() {}


Princesse::Princesse()
{
        nom = "Princesse";
        description = "Si vous défaussez cette carte, vous êtes éliminé de la manche.";
        valeur = 8;
	type = PRINCESSE;
}

Princesse::~Princesse() {}



Pretre::Pretre()
{
        nom = "Pretre";
        description = "Regardez la main d'un autre joueur.";
        valeur = 2;
	type = PRETRE;
}

Pretre::~Pretre() {}

