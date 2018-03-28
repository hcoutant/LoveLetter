#include "Jeu.h"
#include <iostream>
using namespace std;

Jeu::Jeu()    {
    }

Jeu::Jeu(vector<Joueur> Js)    {
    // m_joueurs=Js;
    m_nbJoueurs=Js.size();
    m_joueurActuel=Js[0];	// c'est au premier joueur de jouer
}

Carte Jeu::choisirCarte(Joueur j)    {
    int numCarte;
cout << "Vous devez choisir quelle carte voulez-vous jouer?" << endl;
    cout << "tapez 1 pour choisir la carte " << j.getC1().getNom() << ",\
      ou le 2 pour choisir la carte " << j.getC2().getNom() << endl;
    cin >> numCarte;
      if (numCarte==1)    {
        return j.getC1();
      j.setC1(j.getC2());
     }
     else if (numCarte==2)    {
      return j.getC2();
}
}

Joueur Jeu::choisirJoueur(Joueur jSrc)    {
    int numJoueur;
    cout << "Vous devez choisir un joueur pour appliquer les effets de votre carte." << endl;
    for (int i(0); i<m_joueurs.size(); i++)    {
        cout << "Tapez " << i << " pour choisir le joueur " << m_joueurs[i].getPseudo() << endl;
    }
    cin >> numJoueur;

    if (numJoueur<0 || numJoueur>m_joueurs.size()-1)    {
         cout << "Choix invalide!" << endl;
    }
    return m_joueurs[numJoueur];
}

void Jeu::appliquerEffet(Joueur jSrc, Carte c, Joueur jDst)    {
    // faire un switch sur le champs valeur de la carte passée en param. Si =8 on applique l'effet de la carte princesse, etc.
    // ce champs est protected, pour y accéder depuis cette classe utiliser la méthode getValeur sur la carte.
}

bool Jeu::estTermineeManche()    {
    if (m_joueurs.size()==1)    {
		// s'il ne reste qu'un seul joueur non-éliminé,
        Joueur j=m_joueurs[0];
        j.setM_nbPoints(j.getM_nbPoints()+1);
		// incrémentation du nombre de points de ce joueur.
    return true;
}
    return false;
}

bool Jeu::estTermineJeu()    {
    for (Joueur j: m_joueurs)    {
           if (m_nbJoueurs==2 && j.getM_nbPoints()==7)    {
          return true;
       }
       else if (m_nbJoueurs==3 && j.getM_nbPoints()==5)    {
             return true;
      }
      else if(m_nbJoueurs==4 && j.getM_nbPoints()==4)    {
          return true;
      }
else return false;
   }
}

void Jeu::afficheResultat()    {
    if (estTermineJeu())
        cout << "Affichage des résultats ... " << endl;
}

void Jeu::demarrerJeu()    {
    // à implémenter
}



