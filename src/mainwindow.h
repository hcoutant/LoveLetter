#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "callback.h"

#include <QMainWindow>
#include <QString>
#include <QPushButton>
#include <QTranslator>
#include <QMessageBox>

#include <regex>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void set_index_local(int i);
    void set_nb_joueur(int i);
    void changer_widget(int i);

    void vider_main(int i);
    void vider_defausse(int i);

    void jeter_carte(int i, char* c);
    void jeter_carte(int i, int c, bool d);
    void set_joueur_protege(int i, bool p);

    void set_callBack(CallBack* c);

    void annoncer(char* a);
    void change_score(int i, int s);
    void changer_nombre_carte(int i);
    void activer_fin_de_tour(bool t);

    void afficher_main(int i, int c);

    void set_vainqueur_manche(char* v, char* s);
    void fin_de_partie(char* n);

    void change_affichage(int i);

    void ajouter_joueur(int i, char* n);
    void effacer_pseudo(int i);

    void afficher_pop_up(int i, QString t, QString n);

    void ajouter_carte(int i, int c, char* n);
    void set_index_joueur(int i);

    int nb_joueur;
    bool est_local;
    int index_joueur_courrant;
    bool avecIA;

    void set_qApp(QApplication *qapp);

private slots:
    QString get_chemin_carte(char* n);
    QString get_description_carte(char* n);

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
    void on_btnFinTour_clicked();
    void on_btnContinuer_clicked();
    void on_btnTourSuivant_clicked();
    void on_btnMancheSuivante_clicked();
    void on_btnReseau_clicked();
    void on_btnHote_clicked();
    void on_btnRetourChoixModeJeu2_clicked();
    void on_btnConnexion_clicked();
    void on_btnIA_clicked(); //Bouton pour l'IA !
    void on_btnLangue_clicked();

    void activer_effet_carte(bool g, char* n);
    void activer_garde();

    int get_nb_ciblable();

    void ajouter_defausse(QPushButton* b, int i);

    void on_btnRegle_clicked();

private:
    Ui::MainWindow *ui;

    QApplication *app;

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
    bool est_en_action;
    bool a_joue;

    bool inEnglish;
};

#endif // MAINWINDOW_H
