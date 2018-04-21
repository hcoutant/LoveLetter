#ifndef PRESENTATION_H
#define PRESENTATION_H

#include "mainwindow.h"
#include "callback.h"
#include "joueur.h"
#include "jeu.h"
#include "carte.h"
#include "serveur.h"

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
    Serveur* serveur;

public slots:
    void ajouter_carte(int i, int g, char* n);
    void jeter_carte(int i, int g, bool d);
    void vider_main(int i);
    void vider_defausse(int i);
    void set_index_joueur(int i);
    void changer_nombre_carte(int i);
    void set_joueur_protege(int i, bool p);
    void activer_fin_tour(bool f);
    void fin_partie(char* n);
    void fin_manche(char* v, char* s);
    void ajouter_joueur(int i, char* n);
    void afficher_main(int i, int c);
    void set_index_local(int i);
    void set_nb_joueur(int i);
    void changer_widget(int i);
    void effacer_pseudo(int i);
    void afficher_pop_up(int i, char* t, char* n);

signals:
    void sign_ajouter_carte(int i, int g, char* n);
    void sign_jeter_carte(int i, int g, bool d);
    void sign_vider_main(int i);
    void sign_vider_defausse(int i);
    void sign_set_index_joueur(int i);
    void sign_changer_nombre_carte(int i);
    void sign_set_joueur_protege(int i, bool p);
    void sign_activer_fin_tour(bool f);
    void sign_fin_partie(char* n);
    void sign_fin_manche(char* v, char* s);
    void sign_ajouter_joueur(int i, char* n);
    void sign_afficher_main(int i, int c);
    void sign_set_index_local(int i);
    void sign_set_nb_joueur(int i);
    void sign_changer_widget(int i);
    void sign_effacer_pseudo(int i);
    void sign_afficher_pop_up(int i, char* t, char* n);

private:


    void call(char *a) override;
    void decomposer_action(char* a);

    static int en_route;

    static void lancer_serveur(Serveur* s);
    void eteindre_serveur();

    static void lancer_ecoute(Presentation* p);

    void envoyer_message(char* m);

    int socket_client;

    std::thread* thread_serveur;
    std::thread* thread_ecoute;

    char* buffer_signal;
};

#endif // PRESENTATION_H
