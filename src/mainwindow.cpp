#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reglesjeu.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <regex>

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QComboBox>
#include <QDialog>
#include <QStringList>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLayoutItem>
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    setMinimumSize(QSize(1280, 720));
    ui->setupUi(this);
    ui->wdgListe->setCurrentIndex(0);

    ui->btnCarteGJ1->setVisible(false);
    ui->btnCarteGJ1->setIconSize(QSize(63, 88));
    ui->btnCarteDJ1->setVisible(false);
    ui->btnCarteDJ1->setIconSize(QSize(63, 88));
    ui->btnCarteGJ2->setVisible(false);
    ui->btnCarteGJ2->setIconSize(QSize(63, 88));
    ui->btnCarteDJ2->setVisible(false);
    ui->btnCarteDJ2->setIconSize(QSize(63, 88));
    ui->btnCarteGJ3->setVisible(false);
    ui->btnCarteGJ3->setIconSize(QSize(63, 88));
    ui->btnCarteDJ3->setVisible(false);
    ui->btnCarteDJ3->setIconSize(QSize(63, 88));
    ui->btnCarteGJ4->setVisible(false);
    ui->btnCarteGJ4->setIconSize(QSize(63, 88));
    ui->btnCarteDJ4->setVisible(false);
    ui->btnCarteDJ4->setIconSize(QSize(63, 88));

    ui->cbxNomCarteGarde->addItems({"Pretre", "Baron", "Servante", "Prince", "Roi", "Comtesse", "Princesse"});
    ui->cbxNomCarteGarde->setVisible(false);

    ui->btnValider->setVisible(false);
    ui->btnFinTour->setEnabled(false);

    est_local = true;
    nb_joueur = 0;
    est_en_action = false;

    nom_carte_d_j1 = NULL;
    nom_carte_g_j1 = NULL;
    est_protege_j1 = false;

    nom_carte_d_j2 = NULL;
    nom_carte_g_j2 = NULL;
    est_protege_j2 = false;

    nom_carte_d_j3 = NULL;
    nom_carte_g_j3 = NULL;
    est_protege_j3 = false;

    nom_carte_d_j4 = NULL;
    nom_carte_g_j4 = NULL;
    est_protege_j4 = false;

    nom_carte_jouee = NULL;
    index_joueur = 1;

    action = new char[1024];

    //ui->wdgMenuPrinc->setStyleSheet("background: rgb(0, 255, 255)");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_index_local(int i)
{
    index_joueur = i+1;
    if(index_joueur != 1)
        ui->btnLancerPartie->setEnabled(false);
    else
        ui->btnLancerPartie->setEnabled(true);
}

void MainWindow::changer_widget(int i)
{
    ui->wdgListe->setCurrentIndex(i);
}

void MainWindow::set_nb_joueur(int i)
{
    nb_joueur = i;

    if(nb_joueur >= 3)
    {
        ui->txtPseudoJ3->setVisible(true);
        ui->wdgJ3->setVisible(true);
    }
    else
    {
        ui->txtPseudoJ3->setVisible(false);
        ui->wdgJ3->setVisible(false);
    }

    if(nb_joueur >= 4)
    {
        ui->txtPseudoJ4->setVisible(true);
        ui->wdgJ4->setVisible(true);
    }
    else
    {
        ui->txtPseudoJ4->setVisible(false);
        ui->wdgJ4->setVisible(false);
    }
}

void MainWindow::set_callBack(CallBack* c)
{
    callBack = c;
}

void MainWindow::set_index_joueur(int i)
{
    a_joue = false;
    if(i == 0) i = nb_joueur;
    if(est_local) index_joueur = i;
    index_joueur_courrant = i;

    if(index_joueur == 1) ui->lblTour->setText("Tour de " + ui->lblPseudoJ1->text());
    else if(index_joueur == 2) ui->lblTour->setText("Tour de " + ui->lblPseudoJ2->text());
    else if(index_joueur == 3) ui->lblTour->setText("Tour de " + ui->lblPseudoJ3->text());
    else if(index_joueur == 4) ui->lblTour->setText("Tour de " + ui->lblPseudoJ4->text());

        if(index_joueur_courrant == 1) ui->lblNomJoueurSuivant->setText(QString(ui->lblPseudoJ1->text()));
        else if(index_joueur_courrant == 2) ui->lblNomJoueurSuivant->setText(QString(ui->lblPseudoJ2->text()));
        else if(index_joueur_courrant == 3) ui->lblNomJoueurSuivant->setText(QString(ui->lblPseudoJ3->text()));
        else if(index_joueur_courrant == 4) ui->lblNomJoueurSuivant->setText(QString(ui->lblPseudoJ4->text()));

        ui->wdgListe->setCurrentIndex(7);

        if(index_joueur == 1)
        {
            if(nom_carte_g_j1 == NULL)
            {
                ui->btnCarteGJ1->setEnabled(false);
                ui->btnCarteGJ1->setVisible(false);
            }
            else
            {
                ui->btnCarteGJ1->setIcon(QIcon(QPixmap(get_chemin_carte(nom_carte_g_j1))));
                if(i == index_joueur)
                    ui->btnCarteGJ1->setEnabled(true);
                else
                    ui->btnCarteGJ1->setEnabled(false);
                ui->btnCarteGJ1->setVisible(true);
            }

            if(nom_carte_d_j1 == NULL)
            {
                ui->btnCarteDJ1->setEnabled(false);
                ui->btnCarteDJ1->setVisible(false);
            }
            else
            {
                ui->btnCarteDJ1->setIcon(QIcon(QPixmap(get_chemin_carte(nom_carte_d_j1))));
                if(i == index_joueur)
                    ui->btnCarteDJ1->setEnabled(true);
                else
                    ui->btnCarteDJ1->setEnabled(false);
                ui->btnCarteDJ1->setVisible(true);
            }
        }
        else
        {
            if(nom_carte_g_j1 == NULL)
            {
                ui->btnCarteGJ1->setEnabled(false);
                ui->btnCarteGJ1->setVisible(false);
            }
            else
            {
                ui->btnCarteGJ1->setIcon(QIcon(QPixmap(QCoreApplication::applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "src" + QDir::separator() + "img" + QDir::separator() + "cartes" + QDir::separator() + "Verso.jpg")));
                ui->btnCarteGJ1->setEnabled(false);
                ui->btnCarteGJ1->setVisible(true);
            }

            if(nom_carte_d_j1 == NULL)
            {
                ui->btnCarteDJ1->setEnabled(false);
                ui->btnCarteDJ1->setVisible(false);
            }
            else
            {
                ui->btnCarteDJ1->setIcon(QIcon(QPixmap(QCoreApplication::applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "src" + QDir::separator() + "img" + QDir::separator() + "cartes" + QDir::separator() + "Verso.jpg")));
                ui->btnCarteDJ1->setEnabled(false);
                ui->btnCarteDJ1->setVisible(true);
            }
        }

        if(index_joueur == 2)
        {
            if(nom_carte_g_j2 == NULL)
            {
                ui->btnCarteGJ2->setEnabled(false);
                ui->btnCarteGJ2->setVisible(false);
            }
            else
            {
                ui->btnCarteGJ2->setIcon(QIcon(QPixmap(get_chemin_carte(nom_carte_g_j2))));
                if(i == index_joueur)
                    ui->btnCarteGJ2->setEnabled(true);
                else
                    ui->btnCarteGJ2->setEnabled(false);
                ui->btnCarteGJ2->setVisible(true);
            }

            if(nom_carte_d_j2 == NULL)
            {
                ui->btnCarteDJ2->setEnabled(false);
                ui->btnCarteDJ2->setVisible(false);
            }
            else
            {
                ui->btnCarteDJ2->setIcon(QIcon(QPixmap(get_chemin_carte(nom_carte_d_j2))));
                if(i == index_joueur)
                    ui->btnCarteDJ2->setEnabled(true);
                else
                    ui->btnCarteDJ2->setEnabled(false);
                ui->btnCarteDJ2->setVisible(true);
            }
        }
        else
        {
            if(nom_carte_g_j2 == NULL)
            {
                ui->btnCarteGJ2->setEnabled(false);
                ui->btnCarteGJ2->setVisible(false);
            }
            else
            {
                ui->btnCarteGJ2->setIcon(QIcon(QPixmap(QCoreApplication::applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "src" + QDir::separator() + "img" + QDir::separator() + "cartes" + QDir::separator() + "Verso.jpg")));
                ui->btnCarteGJ2->setEnabled(false);
                ui->btnCarteGJ2->setVisible(true);
            }

            if(nom_carte_d_j2 == NULL)
            {
                ui->btnCarteDJ2->setEnabled(false);
                ui->btnCarteDJ2->setVisible(false);
            }
            else
            {
                ui->btnCarteDJ2->setIcon(QIcon(QPixmap(QCoreApplication::applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "src" + QDir::separator() + "img" + QDir::separator() + "cartes" + QDir::separator() + "Verso.jpg")));
                ui->btnCarteDJ2->setEnabled(false);
                ui->btnCarteDJ2->setVisible(true);
            }
        }

        if(index_joueur == 3)
        {
            if(nom_carte_g_j3 == NULL)
            {
                ui->btnCarteGJ3->setEnabled(false);
                ui->btnCarteGJ3->setVisible(false);
            }
            else
            {
                ui->btnCarteGJ3->setIcon(QIcon(QPixmap(get_chemin_carte(nom_carte_g_j3))));
                if(i == index_joueur)
                    ui->btnCarteGJ3->setEnabled(true);
                else
                    ui->btnCarteGJ3->setEnabled(false);
                ui->btnCarteGJ3->setVisible(true);
            }

            if(nom_carte_d_j3 == NULL)
            {
                ui->btnCarteDJ3->setEnabled(false);
                ui->btnCarteDJ3->setVisible(false);
            }
            else
            {
                ui->btnCarteDJ3->setIcon(QIcon(QPixmap(get_chemin_carte(nom_carte_d_j3))));
                if(i == index_joueur)
                    ui->btnCarteDJ3->setEnabled(true);
                else
                    ui->btnCarteDJ3->setEnabled(false);
                ui->btnCarteDJ3->setVisible(true);
            }
        }
        else
        {
            if(nom_carte_g_j3 == NULL)
            {
                ui->btnCarteGJ3->setEnabled(false);
                ui->btnCarteGJ3->setVisible(false);
            }
            else
            {
                ui->btnCarteGJ3->setIcon(QIcon(QPixmap(QCoreApplication::applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "src" + QDir::separator() + "img" + QDir::separator() + "cartes" + QDir::separator() + "Verso.jpg")));
                ui->btnCarteGJ3->setEnabled(false);
                ui->btnCarteGJ3->setVisible(true);
            }

            if(nom_carte_d_j3 == NULL)
            {
                ui->btnCarteDJ3->setEnabled(false);
                ui->btnCarteDJ3->setVisible(false);
            }
            else
            {
                ui->btnCarteDJ3->setIcon(QIcon(QPixmap(QCoreApplication::applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "src" + QDir::separator() + "img" + QDir::separator() + "cartes" + QDir::separator() + "Verso.jpg")));
                ui->btnCarteDJ3->setEnabled(false);
                ui->btnCarteDJ3->setVisible(true);
            }
        }

        if(index_joueur == 4)
        {
            if(nom_carte_g_j4 == NULL)
            {
                ui->btnCarteGJ4->setEnabled(false);
                ui->btnCarteGJ4->setVisible(false);
            }
            else
            {
                ui->btnCarteGJ4->setIcon(QIcon(QPixmap(get_chemin_carte(nom_carte_g_j4))));
                if(i == index_joueur)
                    ui->btnCarteGJ4->setEnabled(true);
                else
                    ui->btnCarteGJ4->setEnabled(false);
                ui->btnCarteGJ4->setVisible(true);
            }

            if(nom_carte_d_j4 == NULL)
            {
                ui->btnCarteDJ4->setEnabled(false);
                ui->btnCarteDJ4->setVisible(false);
            }
            else
            {
                ui->btnCarteDJ4->setIcon(QIcon(QPixmap(get_chemin_carte(nom_carte_d_j4))));
                if(i == index_joueur)
                    ui->btnCarteDJ4->setEnabled(true);
                else
                    ui->btnCarteDJ4->setEnabled(false);
                ui->btnCarteDJ4->setVisible(true);
            }
        }
        else
        {
            if(nom_carte_g_j4 == NULL)
            {
                ui->btnCarteGJ4->setEnabled(false);
                ui->btnCarteGJ4->setVisible(false);
            }
            else
            {
                ui->btnCarteGJ4->setIcon(QIcon(QPixmap(QCoreApplication::applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "src" + QDir::separator() + "img" + QDir::separator() + "cartes" + QDir::separator() + "Verso.jpg")));
                ui->btnCarteGJ4->setEnabled(false);
                ui->btnCarteGJ4->setVisible(true);
            }

            if(nom_carte_d_j4 == NULL)
            {
                ui->btnCarteDJ4->setEnabled(false);
                ui->btnCarteDJ4->setVisible(false);
            }
            else
            {
                ui->btnCarteDJ4->setIcon(QIcon(QPixmap(QCoreApplication::applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "src" + QDir::separator() + "img" + QDir::separator() + "cartes" + QDir::separator() + "Verso.jpg")));
                ui->btnCarteDJ4->setEnabled(false);
                ui->btnCarteDJ4->setVisible(true);
            }
        }




}

void MainWindow::ajouter_carte(int i, int c, char* n)
{
    if(i == 0) i = nb_joueur;

    int est_comtesse = strcmp(n, "Comtesse");

    if(i == 1)
    {
        if(c == 1)
        {
            nom_carte_g_j1 = n;
            if(index_joueur == 1)
            {
                ui->btnCarteGJ1->setIcon(QIcon(QPixmap(get_chemin_carte(n))));
                ui->btnCarteGJ1->setIconSize(QSize(63, 88));
                ui->btnCarteGJ1->setToolTip(get_description_carte(n));
                if(!a_joue && i == index_joueur)
                    ui->btnCarteGJ1->setEnabled(true);
                else
                    ui->btnCarteGJ1->setEnabled(false);
                if(nom_carte_d_j1 != NULL)
                {
                    if(est_comtesse == 0 && (strcmp(nom_carte_d_j1, "Prince") == 0 || strcmp(nom_carte_d_j1, "Roi") == 0)) ui->btnCarteDJ1->setEnabled(false);
                    if(strcmp(nom_carte_d_j1, "Comtesse") == 0 && (strcmp(n, "Prince") == 0 || strcmp(n, "Roi") == 0)) ui->btnCarteGJ1->setEnabled(false);
                }
            }
            else
            {
                ui->btnCarteGJ1->setIcon(QIcon(QPixmap(QCoreApplication::applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "src" + QDir::separator() + "img" + QDir::separator() + "cartes" + QDir::separator() + "Verso.jpg")));
                ui->btnCarteGJ1->setToolTip("Une carte face verso");
            }
            ui->btnCarteGJ1->setVisible(true);
        }
        else
        {
            nom_carte_d_j1 = n;
            if(index_joueur == 1)
            {
                ui->btnCarteDJ1->setIcon(QIcon(QPixmap(get_chemin_carte(n))));
                ui->btnCarteDJ1->setIconSize(QSize(63, 88));
                ui->btnCarteDJ1->setToolTip(get_description_carte(n));
                if(!a_joue && i == index_joueur)
                    ui->btnCarteDJ1->setEnabled(true);
                else
                    ui->btnCarteDJ1->setEnabled(false);
                if(nom_carte_g_j1 != NULL)
                {
                    if(est_comtesse == 0 && (strcmp(nom_carte_g_j1, "Prince") == 0 || strcmp(nom_carte_g_j1, "Roi") == 0)) ui->btnCarteGJ1->setEnabled(false);
                    if(strcmp(nom_carte_g_j1, "Comtesse") == 0 && (strcmp(n, "Prince") == 0 || strcmp(n, "Roi") == 0)) ui->btnCarteDJ1->setEnabled(false);
                }
            }
            else
            {
                ui->btnCarteDJ1->setIcon(QIcon(QPixmap(QCoreApplication::applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "src" + QDir::separator() + "img" + QDir::separator() + "cartes" + QDir::separator() + "Verso.jpg")));
                ui->btnCarteDJ1->setToolTip("Une carte face verso");
            }
            ui->btnCarteDJ1->setVisible(true);
        }
    }
    else if(i == 2)
    {
        if(c == 1)
        {
            nom_carte_g_j2 = n;
            if(index_joueur == 2)
            {
                ui->btnCarteGJ2->setIcon(QIcon(QPixmap(get_chemin_carte(n))));
                ui->btnCarteGJ2->setIconSize(QSize(63, 88));
                ui->btnCarteGJ2->setToolTip(get_description_carte(n));
                if(!a_joue && i == index_joueur)
                    ui->btnCarteGJ2->setEnabled(true);
                else
                    ui->btnCarteGJ2->setEnabled(false);
                if(nom_carte_d_j2 != NULL)
                {
                    if(est_comtesse == 0 && (strcmp(nom_carte_d_j2, "Prince") == 0 || strcmp(nom_carte_d_j2, "Roi") == 0)) ui->btnCarteDJ2->setEnabled(false);
                    if(strcmp(nom_carte_d_j2, "Comtesse") == 0 && (strcmp(n, "Prince") == 0 || strcmp(n, "Roi") == 0)) ui->btnCarteGJ2->setEnabled(false);
                }
            }
            else
            {
                ui->btnCarteGJ2->setIcon(QIcon(QPixmap(QCoreApplication::applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "src" + QDir::separator() + "img" + QDir::separator() + "cartes" + QDir::separator() + "Verso.jpg")));
                ui->btnCarteGJ2->setToolTip("Une carte face verso");
            }
            ui->btnCarteGJ2->setVisible(true);
        }
        else
        {
            nom_carte_d_j2 = n;
            if(index_joueur == 2)
            {
                ui->btnCarteDJ2->setIcon(QIcon(QPixmap(get_chemin_carte(n))));
                ui->btnCarteDJ2->setIconSize(QSize(63, 88));
                ui->btnCarteDJ2->setToolTip(get_description_carte(n));
                if(!a_joue && i == index_joueur)
                    ui->btnCarteDJ2->setEnabled(true);
                else
                    ui->btnCarteDJ2->setEnabled(false);
                if(nom_carte_g_j2 != NULL)
                {
                    if(est_comtesse == 0 && (strcmp(nom_carte_g_j2, "Prince") == 0 || strcmp(nom_carte_g_j2, "Roi") == 0)) ui->btnCarteGJ2->setEnabled(false);
                    if(strcmp(nom_carte_g_j2, "Comtesse") == 0 && (strcmp(n, "Prince") == 0 || strcmp(n, "Roi") == 0)) ui->btnCarteDJ2->setEnabled(false);
                }
            }
            else
            {
                ui->btnCarteDJ2->setIcon(QIcon(QPixmap(QCoreApplication::applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "src" + QDir::separator() + "img" + QDir::separator() + "cartes" + QDir::separator() + "Verso.jpg")));
                ui->btnCarteDJ2->setToolTip("Une carte face verso");
            }
            ui->btnCarteDJ2->setVisible(true);
        }
    }
    else if(i == 3)
    {
        if(c == 1)
        {
            nom_carte_g_j3 = n;
            if(index_joueur == 3)
            {
                ui->btnCarteGJ3->setIcon(QIcon(QPixmap(get_chemin_carte(n))));
                ui->btnCarteGJ3->setIconSize(QSize(63, 88));
                ui->btnCarteGJ3->setToolTip(get_description_carte(n));
                if(!a_joue && i == index_joueur)
                    ui->btnCarteGJ3->setEnabled(true);
                else
                    ui->btnCarteGJ3->setEnabled(false);
                if(nom_carte_d_j3 != NULL)
                {
                    if(est_comtesse == 0 && (strcmp(nom_carte_d_j3, "Prince") == 0 || strcmp(nom_carte_d_j3, "Roi") == 0)) ui->btnCarteDJ3->setEnabled(false);
                    if(strcmp(nom_carte_d_j3, "Comtesse") == 0 && (strcmp(n, "Prince") == 0 || strcmp(n, "Roi") == 0)) ui->btnCarteGJ3->setEnabled(false);
                }
            }
            else
            {
                ui->btnCarteGJ3->setIcon(QIcon(QPixmap(QCoreApplication::applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "src" + QDir::separator() + "img" + QDir::separator() + "cartes" + QDir::separator() + "Verso.jpg")));
                ui->btnCarteGJ3->setToolTip("Une carte face verso");
            }
            ui->btnCarteGJ3->setVisible(true);
        }
        else
        {
            nom_carte_d_j3 = n;
            if(index_joueur == 3)
            {
                ui->btnCarteDJ3->setIcon(QIcon(QPixmap(get_chemin_carte(n))));
                ui->btnCarteDJ3->setIconSize(QSize(63, 88));
                ui->btnCarteDJ3->setToolTip(get_description_carte(n));
                if(!a_joue && i == index_joueur)
                    ui->btnCarteDJ3->setEnabled(true);
                else
                    ui->btnCarteDJ3->setEnabled(false);
                if(nom_carte_g_j3 != NULL)
                {
                    if(est_comtesse == 0 && (strcmp(nom_carte_g_j3, "Prince") == 0 || strcmp(nom_carte_g_j3, "Roi") == 0)) ui->btnCarteGJ3->setEnabled(false);
                    if(strcmp(nom_carte_g_j3, "Comtesse") == 0 && (strcmp(n, "Prince") == 0 || strcmp(n, "Roi") == 0)) ui->btnCarteDJ3->setEnabled(false);
                }
            }
            else
            {
                ui->btnCarteDJ3->setIcon(QIcon(QPixmap(QCoreApplication::applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "src" + QDir::separator() + "img" + QDir::separator() + "cartes" + QDir::separator() + "Verso.jpg")));
                ui->btnCarteDJ3->setToolTip("Une carte face verso");
            }
            ui->btnCarteDJ3->setVisible(true);
        }
    }
    else if(i == 4)
    {
        if(c == 1)
        {
            nom_carte_g_j4 = n;
            if(index_joueur == 4)
            {
                ui->btnCarteGJ4->setIcon(QIcon(QPixmap(get_chemin_carte(n))));
                ui->btnCarteGJ4->setIconSize(QSize(63, 88));
                ui->btnCarteGJ4->setToolTip(get_description_carte(n));
                if(!a_joue && i == index_joueur)
                    ui->btnCarteGJ4->setEnabled(true);
                else
                    ui->btnCarteGJ4->setEnabled(false);
                if(nom_carte_d_j4 != NULL)
                {
                    if(est_comtesse == 0 && (strcmp(nom_carte_d_j4, "Prince") == 0 || strcmp(nom_carte_d_j4, "Roi") == 0)) ui->btnCarteDJ4->setEnabled(false);
                    if(strcmp(nom_carte_d_j4, "Comtesse") == 0 && (strcmp(n, "Prince") == 0 || strcmp(n, "Roi") == 0)) ui->btnCarteGJ4->setEnabled(false);
                }
            }
            else
            {
                ui->btnCarteGJ4->setIcon(QIcon(QPixmap(QCoreApplication::applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "src" + QDir::separator() + "img" + QDir::separator() + "cartes" + QDir::separator() + "Verso.jpg")));
                ui->btnCarteGJ4->setToolTip("Une carte face verso");
            }
            ui->btnCarteGJ4->setVisible(true);
        }
        else
        {
            nom_carte_d_j4 = n;
            if(index_joueur == 4)
            {
                ui->btnCarteDJ4->setIcon(QIcon(QPixmap(get_chemin_carte(n))));
                ui->btnCarteDJ4->setIconSize(QSize(63, 88));
                ui->btnCarteDJ4->setToolTip(get_description_carte(n));
                if(!a_joue && i == index_joueur)
                    ui->btnCarteDJ4->setEnabled(true);
                else
                    ui->btnCarteDJ4->setEnabled(false);
                if(nom_carte_g_j4 != NULL)
                {
                    if(est_comtesse == 0 && (strcmp(nom_carte_g_j4, "Prince") == 0 || strcmp(nom_carte_g_j4, "Roi") == 0)) ui->btnCarteGJ4->setEnabled(false);
                    if(strcmp(nom_carte_g_j4, "Comtesse") == 0 && (strcmp(n, "Prince") == 0 || strcmp(n, "Roi") == 0)) ui->btnCarteDJ4->setEnabled(false);
                }
            }
            else
            {
                ui->btnCarteDJ4->setIcon(QIcon(QPixmap(QCoreApplication::applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "src" + QDir::separator() + "img" + QDir::separator() + "cartes" + QDir::separator() + "Verso.jpg")));
                ui->btnCarteDJ4->setToolTip("Une carte face verso");
            }
            ui->btnCarteDJ4->setVisible(true);
        }
    }
}

QString MainWindow::get_chemin_carte(char* n)
{
    qDebug() << "chemin: " << n;
    if(strcmp(n, "Garde") == 0)
    {
        return QCoreApplication::applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "src" + QDir::separator() + "img" + QDir::separator() + "cartes" + QDir::separator() + "Garde.png";
    }
    else if(strcmp(n, "Pretre") == 0)
    {
        return QCoreApplication::applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "src" + QDir::separator() + "img" + QDir::separator() + "cartes" + QDir::separator() + "Pretre.png";
    }
    else if(strcmp(n, "Baron") == 0)
    {
        return QCoreApplication::applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "src" + QDir::separator() + "img" + QDir::separator() + "cartes" + QDir::separator() + "Baron.png";
    }
    else if(strcmp(n, "Servante") == 0)
    {
        return QCoreApplication::applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "src" + QDir::separator() + "img" + QDir::separator() + "cartes" + QDir::separator() + "Servante.png";
    }
    else if(strcmp(n, "Prince") == 0)
    {
        return QCoreApplication::applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "src" + QDir::separator() + "img" + QDir::separator() + "cartes" + QDir::separator() + "Prince.png";
    }
    else if(strcmp(n, "Roi") == 0)
    {
        return QCoreApplication::applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "src" + QDir::separator() + "img" + QDir::separator() + "cartes" + QDir::separator() + "Roi.png";
    }
    else if(strcmp(n, "Comtesse") == 0)
    {
        return QCoreApplication::applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "src" + QDir::separator() + "img" + QDir::separator() + "cartes" + QDir::separator() + "Comtesse.png";
    }
    else if(strcmp(n, "Princesse") == 0)
    {
        return QCoreApplication::applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "src" + QDir::separator() + "img" + QDir::separator() + "cartes" + QDir::separator() + "Princesse.png";
    }

    return NULL;

}

QString MainWindow::get_description_carte(char* n)
{
    if(strcmp(n, "Garde") == 0)
    {
        return QString("Choisissez un joueur et essayez de deviner la carte qu'il a en main (excepté le Garde), si vous tombez juste, le joueur est éliminé de la manche.");
    }
    else if(strcmp(n, "Pretre") == 0)
    {
        return QString("Regardez la main d'un autre joueur.");
    }
    else if(strcmp(n, "Baron") == 0)
    {
        return QString("Comparez votre carte avec celle d'un autre joueur, celui qui a la carte avec la plus faible valeur est éliminé de la manche.");
    }
    else if(strcmp(n, "Servante") == 0)
    {
        return QString("Jusqu'au prochain tour, vous êtes protégé des effets des cartes des autres joueurs.");
    }
    else if(strcmp(n, "Prince") == 0)
    {
        return QString("Choisissez un joueur (y compris vous), celui-ci défausse la carte qu'il a en main pour en piocher une nouvelle.");
    }
    else if(strcmp(n, "Roi") == 0)
    {
        return QString("Echangez votre main avec un autre joueur de votre choix.");
    }
    else if(strcmp(n, "Comtesse") == 0)
    {
        return QString("Si vous avez cette carte en main en même temps que le King ou le Prince, alors vous devez défausser la carte de la Comtesse");
    }
    else if(strcmp(n, "Princesse") == 0)
    {
        return QString("si vous défaussez cette carte, vous êtes éliminé de la manche.");
    }

    return NULL;
}

void MainWindow::activer_effet_carte(bool g, char* n)
{
    nom_carte_jouee = n;

    est_en_action = true;

    if(strcmp(n, "Garde") == 0 || strcmp(n, "Pretre") == 0 || strcmp(n, "Baron") == 0 || strcmp(n, "Roi") == 0 || strcmp(n, "Prince") == 0)
    {
        if(index_joueur != 1 && !est_protege_j1)
        {
            if(nom_carte_d_j1 != NULL) ui->btnCarteDJ1->setEnabled(true);
            else ui->btnCarteGJ1->setEnabled(true);
        }
        else
        {
            if(strcmp(n, "Prince") != 0 || est_protege_j1)
            {
                if(g) ui->btnCarteDJ1->setEnabled(false);
                else ui->btnCarteGJ1->setEnabled(false);
            }
            else
            {
                if(g) ui->btnCarteDJ1->setEnabled(true);
                else ui->btnCarteGJ1->setEnabled(true);
            }
        }

        if(index_joueur != 2 && !est_protege_j2)
        {
            if(nom_carte_d_j2 != NULL) ui->btnCarteDJ2->setEnabled(true);
            else ui->btnCarteGJ2->setEnabled(true);
        }
        else
        {
            if(strcmp(n, "Prince") != 0 || est_protege_j2)
            {
                if(g) ui->btnCarteDJ2->setEnabled(false);
                else ui->btnCarteGJ2->setEnabled(false);
            }
            else
            {
                if(g) ui->btnCarteDJ2->setEnabled(true);
                else ui->btnCarteGJ2->setEnabled(true);
            }
        }

        if(index_joueur != 3 && !est_protege_j3)
        {
            if(nom_carte_d_j3 != NULL) ui->btnCarteDJ3->setEnabled(true);
            else ui->btnCarteGJ3->setEnabled(true);
        }
        else
        {
            if(strcmp(n, "Prince") != 0 || est_protege_j3)
            {
                if(g) ui->btnCarteDJ3->setEnabled(false);
                else ui->btnCarteGJ3->setEnabled(false);
            }
            else
            {
                if(g) ui->btnCarteDJ3->setEnabled(true);
                else ui->btnCarteGJ3->setEnabled(true);
            }
        }

        if(index_joueur != 4 && !est_protege_j4)
        {
            if(nom_carte_d_j4 != NULL) ui->btnCarteDJ4->setEnabled(true);
            else ui->btnCarteGJ4->setEnabled(true);
        }
        else
        {
            if(strcmp(n, "Prince") != 0 || est_protege_j4)
            {
                if(g) ui->btnCarteDJ4->setEnabled(false);
                else ui->btnCarteGJ4->setEnabled(false);
            }
            else
            {
                if(g) ui->btnCarteDJ4->setEnabled(true);
                else ui->btnCarteGJ4->setEnabled(true);
            }
        }
    }
}

void MainWindow::remonter_action()
{
    a_joue = true;
    est_en_action = false;
    nom_carte_jouee = NULL;
    callBack->call(action);

    ui->lblAnnonce->setText("");

    /*
    int index_tmp = (index_joueur+1)%nb_joueur;
    if(index_tmp == 0) index_tmp = 2;
    set_index_joueur(index_tmp);
    */
}

void MainWindow::set_joueur_protege(int i, bool p)
{
    if(i == 0) i = nb_joueur;
    if(i == 1) est_protege_j1 = p;
    else if(i == 2) est_protege_j2 = p;
    else if(i == 3) est_protege_j3 = p;
    else if(i == 4) est_protege_j4 = p;
}

void MainWindow::vider_main(int i)
{
    if(i == 0) i = nb_joueur;

    if(i == 1)
    {
        if(nom_carte_g_j1 != NULL) jeter_carte(i, 1, false);
        if(nom_carte_d_j1 != NULL) jeter_carte(i, 2, false);
    }
    if(i == 2)
    {
        if(nom_carte_g_j2 != NULL) jeter_carte(i, 1, false);
        if(nom_carte_d_j2 != NULL) jeter_carte(i, 2, false);
    }
    if(i == 3)
    {
        if(nom_carte_g_j3 != NULL) jeter_carte(i, 1, false);
        if(nom_carte_d_j3 != NULL) jeter_carte(i, 2, false);
    }
    if(i == 4)
    {
        if(nom_carte_g_j4 != NULL) jeter_carte(i, 1, false);
        if(nom_carte_d_j4 != NULL) jeter_carte(i, 2, false);
    }
}

void MainWindow::vider_defausse(int i)
{
    if(i == 0) i = nb_joueur;

    if(i == 1)
    {
        QLayoutItem *child;
        while ((child = ui->hrtDefausseJ1->takeAt(0)) != 0){
            delete child->widget();
        }
    }

    if(i == 2)
    {
        QLayoutItem *child;
        while ((child = ui->hrtDefausseJ2->takeAt(0)) != 0){
            delete child->widget();
        }
    }
    if(i == 3)
    {
        QLayoutItem *child;
        while ((child = ui->hrtDefausseJ3->takeAt(0)) != 0){
            delete child->widget();
        }
    }
    if(i == 4)
    {
        QLayoutItem *child;
        while ((child = ui->hrtDefausseJ4->takeAt(0)) != 0){
            delete child->widget();
        }
    }
}

void MainWindow::ajouter_defausse(QPushButton* b, int i)
{
    if(i == 1)
        ui->hrtDefausseJ1->addWidget(b);
    else if(i == 2)
        ui->hrtDefausseJ2->addWidget(b);
    else if(i == 3)
        ui->hrtDefausseJ3->addWidget(b);
    else if(i == 4)
        ui->hrtDefausseJ4->addWidget(b);
}

void MainWindow::jeter_carte(int i, char *c)
{
    QPushButton* btnTemp = new QPushButton();
    btnTemp->setText(ui->btnCarteGJ1->text());
    btnTemp->setToolTip(get_description_carte(c));
    btnTemp->setEnabled(false);
    btnTemp->setVisible(true);
    btnTemp->setIcon(QIcon(QPixmap(get_chemin_carte(c))));
    btnTemp->setMinimumSize(QSize(63, 88));
    btnTemp->setMaximumSize(QSize(63, 88));
    btnTemp->setIconSize(QSize(63, 88));

    ajouter_defausse(btnTemp, i);
}

void MainWindow::jeter_carte(int i, int c, bool d)
{

    if(i == 0) i = nb_joueur;

    if(i == 1)
    {
        if(c == 1)
        {
            if(d && nom_carte_g_j1 != NULL)
            {
                jeter_carte(i, nom_carte_g_j1);
            }
            nom_carte_g_j1 = NULL;
            ui->btnCarteGJ1->setVisible(false);
            ui->btnCarteGJ1->setEnabled(false);
            ui->btnCarteGJ1->setIcon(QPixmap(""));
        }
        else
        {
            if(d && nom_carte_d_j1 != NULL)
            {
                jeter_carte(i, nom_carte_d_j1);
            }
            nom_carte_d_j1 = NULL;
            ui->btnCarteDJ1->setVisible(false);
            ui->btnCarteDJ1->setEnabled(false);
            ui->btnCarteDJ1->setIcon(QPixmap(""));
        }
    }
    else if(i == 2)
    {
        if(c == 1)
        {
            if(d && nom_carte_g_j2 != NULL)
            {
                jeter_carte(i, nom_carte_g_j2);
            }
            nom_carte_g_j2 = NULL;
            ui->btnCarteGJ2->setVisible(false);
            ui->btnCarteGJ2->setEnabled(false);
            ui->btnCarteGJ2->setIcon(QPixmap(""));
        }
        else
        {
            if(d && nom_carte_d_j2 != NULL)
            {
                jeter_carte(i, nom_carte_d_j2);
            }
            nom_carte_d_j2 = NULL;
            ui->btnCarteDJ2->setVisible(false);
            ui->btnCarteDJ2->setEnabled(false);
            ui->btnCarteDJ2->setIcon(QPixmap(""));
        }
    }
    else if(i == 3)
    {
        if(c == 1)
        {
            if(d && nom_carte_g_j3 != NULL)
            {
                jeter_carte(i, nom_carte_g_j3);
            }
            nom_carte_g_j3 = NULL;
            ui->btnCarteGJ3->setVisible(false);
            ui->btnCarteGJ3->setEnabled(false);
            ui->btnCarteGJ3->setIcon(QPixmap(""));
        }
        else
        {
            if(d && nom_carte_d_j3 != NULL)
            {
                jeter_carte(i, nom_carte_d_j3);
            }
            nom_carte_d_j3 = NULL;
            ui->btnCarteDJ3->setVisible(false);
            ui->btnCarteDJ3->setEnabled(false);
            ui->btnCarteDJ3->setIcon(QPixmap(""));
        }
    }
    else if(i == 4)
    {
        if(c == 1)
        {
            if(d && nom_carte_g_j4 != NULL)
            {
                jeter_carte(i, nom_carte_g_j4);
            }
            nom_carte_g_j4 = NULL;
            ui->btnCarteGJ4->setVisible(false);
            ui->btnCarteGJ4->setEnabled(false);
            ui->btnCarteGJ4->setIcon(QPixmap(""));
        }
        else
        {
            if(d && nom_carte_d_j4 != NULL)
            {
                jeter_carte(i, nom_carte_d_j4);
            }
            nom_carte_d_j4 = NULL;
            ui->btnCarteDJ4->setVisible(false);
            ui->btnCarteDJ4->setEnabled(false);
            ui->btnCarteDJ4->setIcon(QPixmap(""));
        }
    }
}

//Menu principal
void MainWindow::on_btnJouer_clicked()
{
    ui->wdgListe->setCurrentIndex(1);
}

void MainWindow::on_btnQuitter_clicked()
{
    exit(0);
}


//Menu choix mode de jeu
void MainWindow::on_btnLocal_clicked()
{
    est_local = true;
    ui->btnLancerPartie->setEnabled(true);
    ui->wdgListe->setCurrentIndex(2);
}


void MainWindow::on_btnReseau_clicked()
{
    est_local = false;
    ui->wdgListe->setCurrentIndex(8);
}

void MainWindow::on_btnRetourMenuPrinc_clicked()
{
    ui->wdgListe->setCurrentIndex(0);
}


//Menu choix nb_joueur
void MainWindow::on_btn2Joueur_clicked()
{
    ui->txtPseudoJ1->setText(QString(""));
    ui->txtPseudoJ2->setText(QString(""));
    ui->txtPseudoJ3->setText(QString(""));
    ui->txtPseudoJ4->setText(QString(""));
    if(!est_local)
    {
        strcat(action, "|2|");
        strcat(action, ui->lblPseudoReseau->text().toStdString().c_str());
        remonter_action();
        ui->txtPseudoJ1->setReadOnly(true);
        ui->txtPseudoJ2->setReadOnly(true);
    }
    else
    {
        ui->txtPseudoJ1->setReadOnly(false);
        ui->txtPseudoJ2->setReadOnly(false);
    }
    nb_joueur = 2;
    ui->txtPseudoJ3->setVisible(false);
    ui->txtPseudoJ4->setVisible(false);
    ui->wdgListe->setCurrentIndex(3);
}

void MainWindow::on_btn3Joueur_clicked()
{
    ui->txtPseudoJ1->setText(QString(""));
    ui->txtPseudoJ2->setText(QString(""));
    ui->txtPseudoJ3->setText(QString(""));
    ui->txtPseudoJ4->setText(QString(""));
    if(!est_local)
    {
        strcat(action, "|3|");
        strcat(action, ui->lblPseudoReseau->text().toStdString().c_str());
        remonter_action();
        ui->txtPseudoJ1->setReadOnly(true);
        ui->txtPseudoJ2->setReadOnly(true);
        ui->txtPseudoJ3->setReadOnly(true);
    }
    else
    {
        ui->txtPseudoJ1->setReadOnly(false);
        ui->txtPseudoJ2->setReadOnly(false);
        ui->txtPseudoJ3->setReadOnly(false);
    }
    nb_joueur = 3;
    ui->txtPseudoJ3->setVisible(true);
    ui->txtPseudoJ4->setVisible(false);
    ui->wdgListe->setCurrentIndex(3);
}

void MainWindow::on_btn4Joueur_clicked()
{
    ui->txtPseudoJ1->setText(QString(""));
    ui->txtPseudoJ2->setText(QString(""));
    ui->txtPseudoJ3->setText(QString(""));
    ui->txtPseudoJ4->setText(QString(""));
    if(!est_local)
    {
        strcat(action, "|4|");
        strcat(action, ui->lblPseudoReseau->text().toStdString().c_str());
        remonter_action();
        ui->txtPseudoJ1->setReadOnly(true);
        ui->txtPseudoJ2->setReadOnly(true);
        ui->txtPseudoJ3->setReadOnly(true);
        ui->txtPseudoJ4->setReadOnly(true);
    }
    else
    {
        ui->txtPseudoJ1->setReadOnly(false);
        ui->txtPseudoJ2->setReadOnly(false);
        ui->txtPseudoJ3->setReadOnly(false);
        ui->txtPseudoJ4->setReadOnly(false);
    }
    nb_joueur = 4;
    ui->txtPseudoJ3->setVisible(true);
    ui->txtPseudoJ4->setVisible(true);
    ui->wdgListe->setCurrentIndex(3);
}

void MainWindow::on_btnRetourModeJeu_clicked()
{
    ui->wdgListe->setCurrentIndex(1);
}


//Menu Pseudo
void MainWindow::on_btnRetourNbJoueur_clicked()
{
    if(!est_local)
    {
        if(index_joueur == 1)
            strcpy(action, "sht|null");
        else
            strcpy(action, "dcx|null");
        remonter_action();
        ui->wdgListe->setCurrentIndex(8);
    }
    else
        ui->wdgListe->setCurrentIndex(2);
}

void MainWindow::on_btnLancerPartie_clicked()
{
    std::regex regex_pseudo {"([A-Z]|[a-z])+"};
    bool pas_de_blanc = true;

    if(!std::regex_match(ui->txtPseudoJ1->text().toStdString(), regex_pseudo) || !std::regex_match(ui->txtPseudoJ2->text().toStdString(), regex_pseudo))
        pas_de_blanc = false;
    else
    {
        ui->lblPseudoJ1->setText(ui->txtPseudoJ1->text());
        ui->lblPseudoJ2->setText(ui->txtPseudoJ2->text());
    }

    strcpy(action, "str|");
    strcat(action, ui->lblPseudoJ1->text().toStdString().c_str());
    strcat(action, "|");
    strcat(action, ui->lblPseudoJ2->text().toStdString().c_str());

    if(nb_joueur == 2)
    {
        ui->wdgJ3->setVisible(false);
        ui->wdgJ4->setVisible(false);

        est_protege_j3 = true;
        est_protege_j4 = true;
    }
    else if(nb_joueur == 3)
    {
        ui->wdgJ3->setVisible(true);
        ui->wdgJ4->setVisible(false);

        est_protege_j3 = false;
        est_protege_j4 = true;

        if(!std::regex_match(ui->txtPseudoJ3->text().toStdString(), regex_pseudo))
            pas_de_blanc = false;
        else
        {
            ui->lblPseudoJ3->setText(ui->txtPseudoJ3->text());

            strcat(action, "|");
            strcat(action, ui->lblPseudoJ3->text().toStdString().c_str());
        }
    }
    else if(nb_joueur == 4)
    {
        ui->wdgJ3->setVisible(true);
        ui->wdgJ4->setVisible(true);

        est_protege_j3 = false;
        est_protege_j4 = false;

        if(!std::regex_match(ui->txtPseudoJ3->text().toStdString(), regex_pseudo) || !std::regex_match(ui->txtPseudoJ3->text().toStdString(), regex_pseudo))
            pas_de_blanc = false;
        else
        {
            ui->lblPseudoJ3->setText(ui->txtPseudoJ3->text());
            ui->lblPseudoJ4->setText(ui->txtPseudoJ4->text());

            strcat(action, "|");
            strcat(action, ui->lblPseudoJ3->text().toStdString().c_str());
            strcat(action, "|");
            strcat(action, ui->lblPseudoJ4->text().toStdString().c_str());
        }
    }

    if(pas_de_blanc)
    {
        if(est_local)
            ui->wdgListe->setCurrentIndex(4);
        remonter_action();
    }
    else
    {
        int nb_pseudo = 0;
        if(ui->txtPseudoJ1->text() != "") nb_pseudo++;
        if(ui->txtPseudoJ2->text() != "") nb_pseudo++;
        if(ui->txtPseudoJ3->text() != "") nb_pseudo++;
        if(ui->txtPseudoJ4->text() != "") nb_pseudo++;

        if(nb_pseudo != nb_joueur)
            afficher_pop_up(1, "Joueur insuffisant", "Nombre de joueur insuffisant.\nVous ne pouvez pas lancer la partie.");
        else
            afficher_pop_up(1, "Pseudo invalide", "Un ou plusieurs pseudo sont invalides.\nVeuillez entrer des pseudos ne contenant que de lettres.");
    }
}

//Jeu

void MainWindow::on_btnCarteGJ1_clicked()
{
    ui->btnCarteGJ1->setEnabled(false);
    if(!est_en_action && (strcmp(nom_carte_g_j1, "Servante") == 0 || strcmp(nom_carte_g_j1, "Comtesse") == 0  || strcmp(nom_carte_g_j1, "Princesse") == 0))
    {
        strcpy(action, "act|1|1|1");
        remonter_action();
    }
    else if(!est_en_action)
    {
        strcpy(action, "act|1|1");
        if((strcmp(nom_carte_g_j1, "Prince") == 0 && get_nb_ciblable() >= 1) || (strcmp(nom_carte_g_j1, "Prince") != 0 && get_nb_ciblable() >= 2))
        {
            activer_effet_carte(true, nom_carte_g_j1);
        }
        else
        {
            ui->lblAnnonce->setText("Tous les joueurs sont protégés!");
            strcat(action, "|1");
            if(strcmp(nom_carte_g_j1, "Garde") == 0)
                strcat(action, "|Garde");
            remonter_action();
        }
    }
    else
    {
        strcat(action, "|1");
        if(strcmp(nom_carte_jouee, "Garde") == 0)
            activer_garde();
        else
            remonter_action();
        //TODO trouver joueur et remonter action
    }
}

void MainWindow::on_btnCarteDJ1_clicked()
{
    ui->btnCarteDJ1->setEnabled(false);
    if(!est_en_action && (strcmp(nom_carte_d_j1, "Servante") == 0 || strcmp(nom_carte_d_j1, "Comtesse") == 0  || strcmp(nom_carte_d_j1, "Princesse") == 0))
    {
        strcpy(action, "act|1|2|1");
        remonter_action();
    }
    else if(!est_en_action)
    {
        strcpy(action, "act|1|2");
        if((strcmp(nom_carte_d_j1, "Prince") == 0 && get_nb_ciblable() >= 1) || (strcmp(nom_carte_d_j1, "Prince") != 0 && get_nb_ciblable() >= 2))
        {
            ui->lblAnnonce->setText("Choississez une cible!");
            activer_effet_carte(false, nom_carte_d_j1);
        }
        else
        {
            ui->lblAnnonce->setText("Tous les joueurs sont protégés!");
            strcat(action, "|1");
            if(strcmp(nom_carte_d_j1, "Garde") == 0)
                strcat(action, "|Garde");
            remonter_action();
        }
    }
    else
    {
        strcat(action, "|1");
        if(strcmp(nom_carte_jouee, "Garde") == 0)
            activer_garde();
        else
            remonter_action();
        //TODO trouver joueur et remonter action
    }
}

void MainWindow::on_btnCarteGJ2_clicked()
{

    ui->btnCarteGJ2->setEnabled(false);
    if(!est_en_action && (strcmp(nom_carte_g_j2, "Servante") == 0 || strcmp(nom_carte_g_j2, "Comtesse") == 0  || strcmp(nom_carte_g_j2, "Princesse") == 0))
    {
        strcpy(action, "act|2|1|2");
        remonter_action();
    }
    else if(!est_en_action)
    {
        strcpy(action, "act|2|1");
        if((strcmp(nom_carte_g_j2, "Prince") == 0 && get_nb_ciblable() >= 1) || (strcmp(nom_carte_g_j2, "Prince") != 0 && get_nb_ciblable() >= 2))
        {
            ui->lblAnnonce->setText("Choississez une cible!");
            activer_effet_carte(true, nom_carte_g_j2);
        }
        else
        {
            ui->lblAnnonce->setText("Tous les joueurs sont protégés!");
            strcat(action, "|2");
            if(strcmp(nom_carte_g_j2, "Garde") == 0)
                strcat(action, "|Garde");
            remonter_action();
        }
    }
    else
    {
        strcat(action, "|2");
        if(strcmp(nom_carte_jouee, "Garde") == 0)
            activer_garde();
        else
            remonter_action();
        //TODO trouver joueur et remonter action
    }
}

void MainWindow::on_btnCarteDJ2_clicked()
{
    ui->btnCarteDJ2->setEnabled(false);
    if(!est_en_action && (strcmp(nom_carte_d_j2, "Servante") == 0 || strcmp(nom_carte_d_j2, "Comtesse") == 0  || strcmp(nom_carte_d_j2, "Princesse") == 0))
    {
        strcpy(action, "act|2|2|2");
        remonter_action();
    }
    else if(!est_en_action)
    {
        strcpy(action, "act|2|2");
        if((strcmp(nom_carte_d_j2, "Prince") == 0 && get_nb_ciblable() >= 1) || (strcmp(nom_carte_d_j2, "Prince") != 0 && get_nb_ciblable() >= 2))
        {
            ui->lblAnnonce->setText("Choississez une cible!");
            activer_effet_carte(false, nom_carte_d_j2);
        }
        else
        {
            ui->lblAnnonce->setText("Tous les joueurs sont protégés!");
            strcat(action, "|2");
            if(strcmp(nom_carte_d_j2, "Garde") == 0)
                strcat(action, "|Garde");
            remonter_action();
        }
    }
    else
    {
        strcat(action, "|2");
        if(strcmp(nom_carte_jouee, "Garde") == 0)
            activer_garde();
        else
            remonter_action();
        //TODO trouver joueur et remonter action
    }
}

void MainWindow::on_btnCarteGJ3_clicked()
{
    ui->btnCarteGJ3->setEnabled(false);
    if(!est_en_action && (strcmp(nom_carte_g_j3, "Servante") == 0 || strcmp(nom_carte_g_j3, "Comtesse") == 0  || strcmp(nom_carte_g_j3, "Princesse") == 0))
    {
        strcpy(action, "act|3|1|3");
        remonter_action();
    }
    else if(!est_en_action)
    {
        strcpy(action, "act|3|1");
        if((strcmp(nom_carte_g_j3, "Prince") == 0 && get_nb_ciblable() >= 1) || (strcmp(nom_carte_g_j3, "Prince") != 0 && get_nb_ciblable() >= 2))
        {
            ui->lblAnnonce->setText("Choississez une cible!");
            activer_effet_carte(true, nom_carte_g_j3);
        }
        else
        {
            ui->lblAnnonce->setText("Tous les joueurs sont protégés!");
            strcat(action, "|3");
            if(strcmp(nom_carte_g_j3, "Garde") == 0)
                strcat(action, "|Garde");
            remonter_action();
        }
    }
    else
    {
        strcat(action, "|3");
        if(strcmp(nom_carte_jouee, "Garde") == 0)
            activer_garde();
        else
            remonter_action();
        //TODO trouver joueur et remonter action
    }
}

void MainWindow::on_btnCarteDJ3_clicked()
{
    ui->btnCarteDJ3->setEnabled(false);
    if(!est_en_action && (strcmp(nom_carte_d_j3, "Servante") == 0 || strcmp(nom_carte_d_j3, "Comtesse") == 0  || strcmp(nom_carte_d_j3, "Princesse") == 0))
    {
        strcpy(action, "act|3|2|3");
        remonter_action();
    }
    else if(!est_en_action)
    {
        strcpy(action, "act|3|2");
        if((strcmp(nom_carte_d_j3, "Prince") == 0 && get_nb_ciblable() >= 1) || (strcmp(nom_carte_d_j3, "Prince") != 0 && get_nb_ciblable() >= 2))
        {
            ui->lblAnnonce->setText("Choississez une cible!");
            activer_effet_carte(false, nom_carte_d_j3);
        }
        else
        {
            ui->lblAnnonce->setText("Tous les joueurs sont protégés!");
            strcat(action, "|3");
            if(strcmp(nom_carte_d_j3, "Garde") == 0)
                strcat(action, "|Garde");
            remonter_action();
        }
    }
    else
    {
        if(strcmp(nom_carte_jouee, "Garde") == 0)
        {
        }
        strcat(action, "|3");
        if(strcmp(nom_carte_jouee, "Garde") == 0)
            activer_garde();
        else
            remonter_action();
        //TODO trouver joueur et remonter action
    }
}

void MainWindow::on_btnCarteGJ4_clicked()
{
    ui->btnCarteGJ4->setEnabled(false);
    if(!est_en_action && (strcmp(nom_carte_g_j4, "Servante") == 0 || strcmp(nom_carte_g_j4, "Comtesse") == 0  || strcmp(nom_carte_g_j4, "Princesse") == 0))
    {
        strcpy(action, "act|4|1|4");
        remonter_action();
    }
    else if(!est_en_action)
    {
        strcpy(action, "act|4|1");
        if((strcmp(nom_carte_g_j4, "Prince") == 0 && get_nb_ciblable() >= 1) || (strcmp(nom_carte_g_j4, "Prince") != 0 && get_nb_ciblable() >= 2))
        {
            ui->lblAnnonce->setText("Choississez une cible!");
            activer_effet_carte(false, nom_carte_g_j4);
        }
        else
        {
            ui->lblAnnonce->setText("Tous les joueurs sont protégés!");
            strcat(action, "|4");
            if(strcmp(nom_carte_g_j4, "Garde") == 0)
                strcat(action, "|Garde");
            remonter_action();
        }
    }
    else
    {
        strcat(action, "|4");
        if(strcmp(nom_carte_jouee, "Garde") == 0)
            activer_garde();
        else
            remonter_action();
        //TODO trouver joueur et remonter action
    }
}

void MainWindow::on_btnCarteDJ4_clicked()
{
    ui->btnCarteDJ4->setEnabled(false);
    if(!est_en_action && (strcmp(nom_carte_d_j4, "Servante") == 0 || strcmp(nom_carte_d_j4, "Comtesse") == 0  || strcmp(nom_carte_d_j4, "Princesse") == 0))
    {
        strcpy(action, "act|4|2|4");
        remonter_action();
    }
    else if(!est_en_action)
    {
        strcpy(action, "act|4|2");
        if((strcmp(nom_carte_d_j4, "Prince") == 0 && get_nb_ciblable() >= 1) || (strcmp(nom_carte_d_j4, "Prince") != 0 && get_nb_ciblable() >= 2))
        {
            ui->lblAnnonce->setText("Choississez une cible!");
            activer_effet_carte(false, nom_carte_d_j4);
        }
        else
        {
            ui->lblAnnonce->setText("Tous les joueurs sont protégés!");
            strcat(action, "|4");
            if(strcmp(nom_carte_d_j4, "Garde") == 0)
                strcat(action, "|Garde");
            remonter_action();
        }
    }
    else
    {
        strcat(action, "|4");
        if(strcmp(nom_carte_jouee, "Garde") == 0)
            activer_garde();
        else
            remonter_action();
        //TODO trouver joueur et remonter action
    }
}

void MainWindow::on_btnValider_clicked()
{
    strcat(action, "|");
    strcat(action, ui->cbxNomCarteGarde->currentText().toStdString().c_str());

    ui->cbxNomCarteGarde->setVisible(false);
    ui->btnValider->setVisible(false);

    remonter_action();
}

void MainWindow::activer_garde()
{
    ui->lblAnnonce->setText("Choississez une carte!");
    if(nom_carte_g_j1 != NULL) ui->btnCarteGJ1->setEnabled(false);
    if(nom_carte_d_j1 != NULL) ui->btnCarteDJ1->setEnabled(false);
    if(nom_carte_g_j2 != NULL) ui->btnCarteGJ2->setEnabled(false);
    if(nom_carte_d_j2 != NULL) ui->btnCarteDJ2->setEnabled(false);
    if(nom_carte_g_j3 != NULL) ui->btnCarteGJ3->setEnabled(false);
    if(nom_carte_d_j3 != NULL) ui->btnCarteDJ3->setEnabled(false);
    if(nom_carte_g_j4 != NULL) ui->btnCarteGJ4->setEnabled(false);
    if(nom_carte_d_j4 != NULL) ui->btnCarteDJ4->setEnabled(false);

    ui->cbxNomCarteGarde->setVisible(true);
    ui->btnValider->setVisible(true);
}

int MainWindow::get_nb_ciblable()
{
    int nb_ciblable = 0;
    std::cout <<std::endl<<std::endl;
    if(!est_protege_j1)
    {
        nb_ciblable++;
        std::cout <<"j1 ciblable"<<std::endl;
    }
    if(!est_protege_j2){
        nb_ciblable++;
        std::cout <<"j2 ciblable"<<std::endl;
    }
    if(!est_protege_j3 && nb_joueur >= 3)
    {
        nb_ciblable++;
        std::cout <<"j3 ciblable"<<std::endl;
    }
    if(!est_protege_j4 && nb_joueur == 4)
    {
        nb_ciblable++;
        std::cout <<"j4 ciblable"<<std::endl;
    }
    std::cout <<std::endl<<std::endl;
    return nb_ciblable;
}

void MainWindow::on_btnFinTour_clicked()
{
    strcpy(action, "trn|null");
    remonter_action();
}

void MainWindow::annoncer(char* a)
{
    ui->lblAnnonce->setText(a);
}

void MainWindow::changer_nombre_carte(int i)
{
    char label_carte[50];
    sprintf(label_carte ,"nombre de cartes restantes: %d",  i);

    ui->lblCartesRestantes->setText(label_carte);
}

void MainWindow::activer_fin_de_tour(bool t)
{
    ui->btnFinTour->setEnabled(t);
}

void MainWindow::fin_de_partie(char* n)
{
    ui->wdgListe->setCurrentIndex(5);
    ui->lblGagnant->setText(n);
}

void MainWindow::on_btnContinuer_clicked()
{
    ui->wdgListe->setCurrentIndex(3);
}

void MainWindow::afficher_main(int i, int c)
{
    if(i == 0) i = nb_joueur;

    if(i == 1)
    {
        if(c == 2)
        {
            qDebug() << "DJ1 " << nom_carte_d_j1;
            ui->btnCarteDJ1->setIcon(QIcon(QPixmap(get_chemin_carte(nom_carte_d_j1))));
            ui->btnCarteDJ1->setToolTip(get_description_carte(nom_carte_d_j1));
        }
        if(c == 1)
        {
            qDebug() << "DJ2 " << nom_carte_d_j2;
            ui->btnCarteGJ1->setIcon(QIcon(QPixmap(get_chemin_carte(nom_carte_g_j1))));
            ui->btnCarteGJ1->setToolTip(get_description_carte(nom_carte_g_j1));
        }
    }
    else if(i == 2)
    {
        if(c == 2)
        {
            ui->btnCarteDJ2->setIcon(QIcon(QPixmap(get_chemin_carte(nom_carte_d_j2))));
            ui->btnCarteDJ2->setToolTip(get_description_carte(nom_carte_d_j2));
        }
        if(c == 1)
        {
            ui->btnCarteGJ2->setIcon(QIcon(QPixmap(get_chemin_carte(nom_carte_g_j2))));
            ui->btnCarteGJ2->setToolTip(get_description_carte(nom_carte_g_j2));
        }
    }
    else if(i == 3)
    {
        if(c == 2)
        {
            ui->btnCarteDJ3->setIcon(QIcon(QPixmap(get_chemin_carte(nom_carte_d_j3))));
            ui->btnCarteDJ3->setToolTip(get_description_carte(nom_carte_d_j3));
        }
        if(c == 1)
        {
            ui->btnCarteGJ3->setIcon(QIcon(QPixmap(get_chemin_carte(nom_carte_g_j3))));
            ui->btnCarteGJ3->setToolTip(get_description_carte(nom_carte_g_j3));
        }
    }
    else if(i == 4)
    {
        if(c == 2)
        {
            ui->btnCarteDJ4->setIcon(QIcon(QPixmap(get_chemin_carte(nom_carte_d_j4))));
            ui->btnCarteDJ4->setToolTip(get_description_carte(nom_carte_d_j4));
        }
        if(c == 1)
        {
            ui->btnCarteGJ4->setIcon(QIcon(QPixmap(get_chemin_carte(nom_carte_g_j4))));
            ui->btnCarteGJ4->setToolTip(get_description_carte(nom_carte_g_j4));
        }
    }
}

void MainWindow::on_btnTourSuivant_clicked()
{
    ui->lblNomJoueurSuivant->setText(QString(""));
    ui->wdgListe->setCurrentIndex(4);
}

void MainWindow::on_btnMancheSuivante_clicked()
{
    ui->lblVainqueurManche->setText(QString(""));
    ui->wdgListe->setCurrentIndex(7);
}

void MainWindow::set_vainqueur_manche(char * v, char* s)
{
    ui->lblVainqueurManche->setText(v);
    ui->lblScores->setText(s);

    ui->wdgListe->setCurrentIndex(6);
}


void MainWindow::on_btnHote_clicked()
{
    strcpy(action, "hst");
    ui->wdgListe->setCurrentIndex(2);
}

void MainWindow::change_affichage(int i)
{
    ui->wdgListe->setCurrentIndex(i);
}

void MainWindow::ajouter_joueur(int i, char* n)
{
    i = i+1;
    if(i == 1)
    {
        ui->txtPseudoJ1->setText(QString(n));
        ui->lblPseudoJ1->setText(QString(n));
    }
    else if(i == 2)
    {
        ui->txtPseudoJ2->setText(QString(n));
        ui->lblPseudoJ2->setText(QString(n));
    }
    else if(i == 3)
    {
        ui->txtPseudoJ3->setText(QString(n));
        ui->lblPseudoJ3->setText(QString(n));
    }
    else if(i == 4)
    {
        ui->txtPseudoJ4->setText(QString(n));
        ui->lblPseudoJ4->setText(QString(n));
    }
}

void MainWindow::effacer_pseudo(int i)
{
    i = i+1;
    if(i == 1) ui->txtPseudoJ1->setText(QString(""));
    else if(i == 2) ui->txtPseudoJ2->setText(QString(""));
    else if(i == 3) ui->txtPseudoJ3->setText(QString(""));
    else if(i == 4) ui->txtPseudoJ4->setText(QString(""));
}

void MainWindow::on_btnRetourChoixModeJeu2_clicked()
{
    ui->wdgListe->setCurrentIndex(1);
}

void MainWindow::on_btnConnexion_clicked()
{
    std::regex regex_ip {"([0-2]?[0-9]?[0-9]).([0-2]?[0-9]?[0-9]).([0-2]?[0-9]?[0-9]).([0-2]?[0-9]?[0-9])"};
    std::regex regex_pseudo {"([A-Z]|[a-z])+"};

    if(std::regex_match(ui->lblIP->text().toStdString(), regex_ip))
    {
        if(ui->lblPseudoReseau->text() != "" && std::regex_match(ui->lblPseudoReseau->text().toStdString(), regex_pseudo))
        {
            strcpy(action, "cnx|");
            strcat(action, ui->lblIP->text().toStdString().c_str());
            strcat(action, "|");
            strcat(action, ui->lblPseudoReseau->text().toStdString().c_str());
            remonter_action();
        }
        else
        {
            qDebug() << "erreur pseudo";
            //TODO "Veuillez entrer un pseudo valide"
        }
    }
    else
    {
        qDebug() << "erreur ip";
        //TODO "Veuillez entrer une adresse ip valide"
    }
}

void MainWindow::afficher_pop_up(int i, char* t, char*n)
{
    if(i == 1) QMessageBox::information(this, t, n);
    else if(i == 2) QMessageBox::warning(this, t, n);
    else if(i == 3) QMessageBox::critical(this, t, n);
}

void MainWindow::on_btnRegle_clicked()
{
    ReglesJeu *rj = new ReglesJeu;
    rj->show();
}
