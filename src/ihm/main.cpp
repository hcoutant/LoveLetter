#include "fenetre.h"
#include <QApplication>
#include <QPushButton>

int main(int argc, char** argv)
{
	QApplication a(argc,argv);
	Fenetre w;
	w.show();
	return a.exec();
}
