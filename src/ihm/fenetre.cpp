#include "fenetre.h"
#include "ui_fenetre.h"
#include "reglesjeu.h"

//constructeur fenetre principale
Fenetre::Fenetre(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Fenetre)
{
    ui->setupUi(this);

    ui->infoTipModeJeu->setPlainText("Survolez les boutons avec votre souris pour afficher les détails du mode de jeu.");

    //ajout icone sur bouton de jeu multijoueur sur meme machine
    ui->btn2Joueurs1Pc->setIcon(QIcon("btn_2players_1PC.png"));
    ui->btn2Joueurs1Pc->setIconSize(QSize(170,101));

    //ajout icone sur bouton de jeu en réseau
    ui->btnJeuReseau->setIcon(QIcon("btn_2players_networks.png"));
    ui->btnJeuReseau->setIconSize(QSize(170,101));

    //ajout icone sur bouton de jeu contre IA
    ui->btnJeuIA->setIcon(QIcon("btn_1player_IA.png"));
    ui->btnJeuIA->setIconSize(QSize(170,101));

    //mise en place du mécanisme de hover sur les boutons de mode de jeu.
    ui->btn2Joueurs1Pc->installEventFilter(this);
    ui->btnJeuReseau->installEventFilter(this);
    ui->btnJeuIA->installEventFilter(this);

    /*connecte les differents bouton quitter au dialogue de confirmation*/
    connect(ui->btnQuitter_2 , SIGNAL(clicked()), this, SLOT(confirmerQuitter()));
    connect(ui->btnQuitter_3 , SIGNAL(clicked()), this, SLOT(confirmerQuitter()));
    connect(ui->btnQuitter_4 , SIGNAL(clicked()), this, SLOT(confirmerQuitter()));
}

//destructeur
Fenetre::~Fenetre()
{
    delete ui;
}

//methode event bouton quitter : quitte l'application
void Fenetre::on_btnQuitter_clicked()
{
    this->close();
}

/*methode event bouton règles du jeu :
 * ouvre une fenetre contenant les règles du jeu
 * on peut maintenir cette fenetre ouverte indépendamment de la
 * fenetre de jeu*/
void Fenetre::on_btnReglesJeu_clicked()
{
    ReglesJeu *rj = new ReglesJeu;
    rj->show();
}

/*methode event bouton jouer
    envoie vers l'écran de choix du mode de jeu.
*/
void Fenetre::on_btnJouer_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Fenetre::on_btnQuitter_2_clicked()
{

}


void Fenetre::on_btnRetour_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->infoTipModeJeu->setPlainText("Survolez les boutons avec votre souris pour afficher les détails du mode de jeu.");
}

/*methode d'implementation hover de souris sur les boutons de choix
 * du mode de jeu, au hover de la souris, une info sur le mode de
 * jeu est affichée dans la plaintextarea infoTipModeJeu qui se trouve
   sous les boutons mode de jeu*/
bool Fenetre::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == (QObject*)ui->btn2Joueurs1Pc) {
        if (event->type() == QEvent::Enter) {
            ui->infoTipModeJeu->setPlainText("Mode multi joueurs sur un ordinateur : dans ce mode vous enchaînerez les tours alternativement sur le même écran, mais les tours seront séparés par des écrans de transition pour préserver la discrétion des mains des joueurs !");
        }
        return QWidget::eventFilter(obj, event);

    } else if(obj == (QObject*)ui->btnJeuReseau)  {
        if (event->type() == QEvent::Enter) {
            ui->infoTipModeJeu->setPlainText("Mode multi joueurs en réseau : dans ce mode vous jouerez contre des adversaires se trouvant sur d'autres machines à distance !");
        }
        return QWidget::eventFilter(obj, event);
    } else if(obj == (QObject*)ui->btnJeuIA)  {
        if (event->type() == QEvent::Enter) {
            ui->infoTipModeJeu->setPlainText("Mode joueur solo contre Intelligence Artificielle : dans ce mode vous affronterez votre propre ordinateur !");
        }
        return QWidget::eventFilter(obj, event);
    } else {
        return QWidget::eventFilter(obj, event);
    }
}

/* methode event bouton multijoueurs sur meme machine
 * envoie vers l'écran de choix du nom des joueurs
*/
void Fenetre::on_btn2Joueurs1Pc_clicked()
{
    ui->infoTipModeJeu->setPlainText("Survolez les boutons avec votre souris pour afficher les détails du mode de jeu.");
    ui->stackedWidget->setCurrentIndex(2);
}

/*retour vers l'ecran de choix de mode de jeu*/
void Fenetre::on_btnRetourChoixJeu_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

/*ouvre le dialogue de confirmation pour quitter l'application*/
void Fenetre::confirmerQuitter()
{
    int reponse = QMessageBox::question(this, "Confirmation", "Etes-vous sûr(e) de vouloir quitter Love Letter ?", QMessageBox::Yes | QMessageBox::No);


        if (reponse == QMessageBox::Yes)
        {

            close();
        }

}

void Fenetre::on_btnCommencer2joueurs_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}
