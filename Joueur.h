#include "Carte.h"

class Joueur    {
    public:
      Joueur();
      Joueur(std::string username, Carte cg, Carte cd);
       bool estElimine();
        bool estProtege();
      void setElimine();
      void setProtege();
      std::string getPseudo();
      Carte getC1();
      Carte getC2();
      int getM_nbPoints();
      void setC1(Carte c);
      void setC2(Carte c);
      void setM_nbPoints(int nbPoints);

    protected:
      std::string pseudo;
      bool elimine;
      bool protege;
      int m_nbPoints;
      Carte c1;
      Carte c2;

};
