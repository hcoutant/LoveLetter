#ifndef REGLESJEU_H
#define REGLESJEU_H

#include <QDialog>

namespace Ui {
class ReglesJeu;
}

class ReglesJeu : public QDialog
{
    Q_OBJECT

public:
    explicit ReglesJeu(QWidget *parent = 0);
    ~ReglesJeu();

private slots:
    void on_btnQuitter_clicked();

private:
    Ui::ReglesJeu *ui;
};

#endif // REGLESJEU_H
