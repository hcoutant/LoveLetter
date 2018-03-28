#include "Carte.h"
using namespace std;

Carte::Carte() {}
	
int Carte::getValeur()    {
    return valeur;
}

string Carte::getNom()    {
    return nom;
}

string Carte::getEffet()    {
    return effet;
}

Princesse::Princesse()    {
    valeur=8;
    nom="Princesse";
    effet="Si vous vous défaussez de cette carte vous êtes éliminé de cette manche";
}

Comtesse::Comtesse()    {
    valeur=7;
    nom="Comtesse";
    effet="Si vous avez le Roi ou le Prince en même temps que cette carte,\
        vous devez la défausser";
}

Roi::Roi()    {
    valeur=6;
    nom="Roi";
    effet="Vous pouvez échanger votre jeu avec un autre joueur de votre choix";
}

Prince::Prince()    {
    valeur=5;
    nom="Prince";
   effet="Vous devez choisir un joueur, y compris vous, celui-ci devra\
        défausser sa carte pour piocher une nouvell";
}

Servante::Servante()    {
    valeur=4;
    nom="Servante";
    effet="Vous êtes protégé des effets des autres cartes\
        jusqu'au prochain tour";
}

Baron::Baron()    {
    valeur=3;
    nom="Baron";
    effet="Vous devez comparer votre carte avec celle d'un autre joueur, et\
        celui qui a la carte la plus faible sera éliminé de la manche";
}

Pretre::Pretre()    {
    valeur=2;
    nom="Pretre";
    effet="Vous pouvez regarder la carte d'un autre joueur de votre choix";
}

Garde::Garde()    {
    valeur=1;
    nom="Garde";
    effet="Vous devez choisir un joueur et deviner sa carte, excepté\
        le Garde. Si vous tombez juste ce joueur sera éliminé";
}





