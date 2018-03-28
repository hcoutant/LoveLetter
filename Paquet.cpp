#include <algorithm>
#include <ctime>
// #include <random>
#include "Paquet.h"
using namespace std;

Paquet::Paquet()    {
    }

Paquet::Paquet(int nbCartes)    {
    m_nbCartes=nbCartes;
    m_cartes.reserve(nbCartes);
    m_cartes.push_back(Princesse());
    m_cartes.push_back(Comtesse());
    m_cartes.push_back(Roi());
     m_cartes.push_back(Prince());
    m_cartes.push_back(Prince());
    m_cartes.push_back(Servante());
    m_cartes.push_back(Servante());
    m_cartes.push_back(Baron());
    m_cartes.push_back(Baron());
    m_cartes.push_back(Pretre());
    m_cartes.push_back(Pretre());
    m_cartes.push_back(Garde());
    m_cartes.push_back(Garde());
    m_cartes.push_back(Garde());
    m_cartes.push_back(Garde());
    m_cartes.push_back(Garde());
}

void Paquet::melanger()    {
    /*  int n;
    srand((int)time(0));
    n=(rand() % m_nbCartes);
     random_shuffle(m_cartes.front(), m_cartes.back(), n); 
    shuffle(begin(m_cartes),end(m_cartes), default_random_engine()); */
}

Carte Paquet::piocher(Joueur j)    {
    Carte c=m_cartes.back();
    m_cartes.pop_back();
    m_nbCartes--;
    j.setC2(c);
}

void Paquet::deffausser(Joueur j, Carte c)    {
    m_cartes.push_back(c);
    m_nbCartes++;
    }
