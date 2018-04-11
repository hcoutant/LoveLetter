#ifndef FENETRE_H
#define FENETRE_H

#include <QMainWindow>
#include <QMessageBox>


namespace Ui {
class Fenetre;
}

class Fenetre : public QMainWindow
{
    Q_OBJECT

public:
    explicit Fenetre(QWidget *parent = 0);
    ~Fenetre();

    bool eventFilter(QObject *obj, QEvent *event);

private slots:

    void on_btnQuitter_clicked();

    void on_btnReglesJeu_clicked();

    void on_btnJouer_clicked();

    void on_btnQuitter_2_clicked();

    void on_btnRetour_clicked();

    void on_btn2Joueurs1Pc_clicked();

    void on_btnRetourChoixJeu_clicked();

    void confirmerQuitter();

    void on_btnCommencer2joueurs_clicked();

private:
    Ui::Fenetre *ui;
};

#endif // FENETRE_H
