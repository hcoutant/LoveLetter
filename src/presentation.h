#ifndef PRESENTATION_H
#define PRESENTATION_H

#include "mainwindow.h"
#include "callback.h"
#include "joueur.h"
#include "jeu.h"
#include "carte.h"

#include <QApplication>
#include <QObject>

#include <mutex>
#include <condition_variable>

#include <vector>

class Presentation: public CallBack
{
    Q_OBJECT
public:
    Presentation();

    int lancer_fenetre(int argc, char *argv[]);

    void ajouter_main(int i);

    Jeu* jeu;
    std::vector<Joueur*> liste_joueur;
    std::vector<char*> instructions;

    MainWindow* w;

    int index_joueur_actuel;

private:

    void call(char *a) override;
    void decomposer_action(char* a);



};

#endif // PRESENTATION_H
