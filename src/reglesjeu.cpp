#include "reglesjeu.h"
#include "ui_reglesjeu.h"

//fenetre popup présentant les règles du jeu
ReglesJeu::ReglesJeu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReglesJeu)
{
    ui->setupUi(this);
}

ReglesJeu::~ReglesJeu()
{
    delete ui;
}

void ReglesJeu::on_btnQuitter_clicked()
{
    this->close();
}
