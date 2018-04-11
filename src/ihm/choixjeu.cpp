

ChoixJeu::ChoixJeu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChoixJeu)
{
    ui->setupUi(this);
}

ChoixJeu::~ChoixJeu()
{
    delete ui;
}
