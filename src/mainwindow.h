#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "callback.h"

#include <QMainWindow>
#include <QString>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void vider_main(int i);
    void vider_defausse(int i);

    void jeter_carte(int i, int c, bool d);
    void set_joueur_protege(int i, bool p);

    void set_callBack(CallBack* c);

    void annoncer(char* a);
    void change_score(int i, int s);
    void changer_nombre_carte(int i);
    void activer_fin_de_tour(bool t);
    void fin_de_partie(char* n);

    void afficher_main(int i);

    int nb_joueur;

public slots:
    void ajouter_carte(int i, char* n);
    void set_index_joueur(int i);

private slots:
    QString get_chemin_carte(char* n);
    QString get_description_carte(char* n);

    void activer_effet_carte(bool g, char* n);
    void remonter_action();

    void on_btnJouer_clicked();
    void on_btnQuitter_clicked();

    void on_btnLocal_clicked();
    void on_btnRetourMenuPrinc_clicked();

    void on_btn2Joueur_clicked();
    void on_btn3Joueur_clicked();
    void on_btn4Joueur_clicked();
    void on_btnRetourModeJeu_clicked();

    void on_btnLancerPartie_clicked();
    void on_btnRetourNbJoueur_clicked();

    void on_btnCarteGJ1_clicked();
    void on_btnCarteDJ1_clicked();
    void on_btnCarteGJ2_clicked();
    void on_btnCarteDJ2_clicked();
    void on_btnCarteGJ3_clicked();
    void on_btnCarteDJ3_clicked();
    void on_btnCarteGJ4_clicked();
    void on_btnCarteDJ4_clicked();

    void on_btnValider_clicked();
    void activer_garde();

    int get_nb_ciblable();
    void on_btnFinTour_clicked();

    void on_btnContinuer_clicked();

private:
    Ui::MainWindow *ui;

    CallBack* callBack;

    char* action;

    char* nom_carte_d_j1;
    char* nom_carte_g_j1;
    bool est_protege_j1;

    char* nom_carte_d_j2;
    char* nom_carte_g_j2;
    bool est_protege_j2;

    char* nom_carte_d_j3;
    char* nom_carte_g_j3;
    bool est_protege_j3;

    char* nom_carte_d_j4;
    char* nom_carte_g_j4;
    bool est_protege_j4;

    char* nom_carte_jouee;

    int index_joueur;
    bool est_local;
    bool est_en_action;
    bool a_joue;
};

#endif // MAINWINDOW_H
