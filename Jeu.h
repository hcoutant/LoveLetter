#include <vector>
#include "Paquet.h"

class Jeu    {
    public:
      Jeu();
      Jeu(std::vector<Joueur> Js);
      void demarrerJeu();
      Carte choisirCarte(Joueur j);
      Joueur choisirJoueur(Joueur jSrc);
      void appliquerEffet(Joueur jSrc, Carte c, Joueur jDst);
      bool estTermineeManche();
      bool estTermineJeu();
    void afficheResultat();

    protected:
      int m_nbJoueurs;
      Joueur m_joueurActuel;
      Paquet m_paquet;
      Paquet m_deffausse;
      std::vector<Carte> m_deposees;
      std::vector<Joueur> m_joueurs;
       std::vector<Joueur> m_joueursElimines;

};

