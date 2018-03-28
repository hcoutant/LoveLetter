#include "Joueur.h"
using namespace std;

Joueur::Joueur()    {
    elimine=false;
    protege=false;
    m_nbPoints=0;
    }

Joueur::Joueur(string username, Carte cg, Carte cd)    {
    pseudo=username;
    c1=cg;
    c2=cd;
}
 
bool Joueur::estElimine()    {
    return elimine;
}

bool Joueur::estProtege()    {
    return protege;
}

void Joueur::setElimine()    {
    elimine=true;
}

void Joueur::setProtege()    {
    protege=true;
}

	// des geters et seters pour certains attributs 
        // qui doivent être utilisés dans le fichier Jeu.cpp

string Joueur::getPseudo()    {
    return pseudo;
}

Carte Joueur::getC1()    {
    return c1;
}

Carte Joueur::getC2()    {
    return c2;
}

int Joueur::getM_nbPoints()    {
    return m_nbPoints;
}

void Joueur::setC1(Carte c)    {
    c1=c;
}

void Joueur::setC2(Carte c)    {
    c2=c;
}

void Joueur::setM_nbPoints(int nbPoints)    {
    m_nbPoints=nbPoints;
}
