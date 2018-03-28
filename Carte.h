#ifndef DEF_CARTE_H
#define DEF_CARTE_H
#include <string>

class Carte    {
    public:
 Carte();
    int getValeur();
    std::string getNom();
    std::string getEffet();
   
    protected:
      int valeur;
      std::string nom;
      std::string effet;
};

class Princesse: public Carte    {
    public:
      Princesse();
};

class Comtesse: public Carte    {
    public:
      Comtesse();
};

class Roi: public Carte    {
    public:
      Roi();
};

class Prince: public Carte    {
    public:
      Prince();
};

class Servante: public Carte    {
    public:
      Servante();
};

class Baron: public Carte    {
    public:
      Baron();
};

class Pretre: public Carte    {
    public:
      Pretre();
};

class Garde: public Carte    {
    public:
      Garde();
};
  
#endif
