#include <vector>
#include "Joueur.h"

class Paquet    {
    public:
      Paquet();
      Paquet(int nbCartes);
      void melanger();
Carte piocher(Joueur j);
      void deffausser(Joueur j, Carte c);
    
    protected:
      int m_nbCartes;
      std::vector<Carte> m_cartes;
};
