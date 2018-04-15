#include "mainwindow.h"
#include "presentation.h"

int main(int argc, char *argv[])
{
    Presentation* p = new Presentation();
    p->lancer_fenetre(argc, argv);

    return 0;
}
