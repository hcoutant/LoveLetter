#include "presentation.h"

#include <QDebug>
#include <QObject>
#include <QString>

Presentation::Presentation()
{
}

int Presentation::lancer_fenetre(int argc, char *argv[])
{
    QApplication a(argc, argv);
    w = new MainWindow;

    CallBack* c = this;

    w->set_callBack(c);

    w->show();

    return a.exec();
}

void lancer_partie(){

}

void Presentation::decomposer_action(char* a)
{
    instructions.clear();

    char* token = strtok(a, "|");

    while(token != NULL)
    {
        instructions.push_back(token);
        token = strtok(NULL, "|");
    }
}

void Presentation::call(char* a){

    qDebug() << a;

    QString te((const char*)a);

    decomposer_action(a);

    if(strcmp(instructions[0], "str") == 0)
    {
        Joueur* j1 = new Joueur(std::string(instructions[1]));
        Joueur* j2 = new Joueur(std::string(instructions[2]));
        Joueur* j3;
        Joueur* j4;

        liste_joueur.push_back(j1);
        liste_joueur.push_back(j2);

        if(w->nb_joueur >= 3)
        {
            j3 = new Joueur(std::string(instructions[3]));
            liste_joueur.push_back(j3);
        }
        if(w->nb_joueur >= 4)
        {
            j4 = new Joueur(std::string(instructions[4]));
            liste_joueur.push_back(j4);
        }

        jeu = new Jeu(liste_joueur);

        j1->ajouterJeu(jeu);
        j2->ajouterJeu(jeu);
        if(w->nb_joueur >= 3) j3->ajouterJeu(jeu);
        if(w->nb_joueur >= 4) j4->ajouterJeu(jeu);

        jeu->initialisation();

        for(unsigned int i = 0; i < liste_joueur.size(); i++)
        {
            if(liste_joueur[i]->getCarteMg() != nullptr)
            {
                if(liste_joueur[i]->getCarteMg()->affiche() == "Garde") w->ajouter_carte((i+1)%w->nb_joueur, "Garde");
                else if(liste_joueur[i]->getCarteMg()->affiche() == "Pretre") w->ajouter_carte((i+1)%w->nb_joueur, "Pretre");
                else if(liste_joueur[i]->getCarteMg()->affiche() == "Baron") w->ajouter_carte((i+1)%w->nb_joueur, "Baron");
                else if(liste_joueur[i]->getCarteMg()->affiche() == "Servante") w->ajouter_carte((i+1)%w->nb_joueur, "Servante");
                else if(liste_joueur[i]->getCarteMg()->affiche() == "Prince") w->ajouter_carte((i+1)%w->nb_joueur, "Prince");
                else if(liste_joueur[i]->getCarteMg()->affiche() == "Roi") w->ajouter_carte((i+1)%w->nb_joueur, "Roi");
                else if(liste_joueur[i]->getCarteMg()->affiche() == "Comtesse") w->ajouter_carte((i+1)%w->nb_joueur, "Comtesse");
                else if(liste_joueur[i]->getCarteMg()->affiche() == "Princesse") w->ajouter_carte((i+1)%w->nb_joueur, "Princesse");
            }
            if(liste_joueur[i]->getCarteMd() != nullptr)
            {
                if(liste_joueur[i]->getCarteMd()->affiche() == "Garde") w->ajouter_carte((i+1)%w->nb_joueur, "Garde");
                else if(liste_joueur[i]->getCarteMd()->affiche() == "Pretre") w->ajouter_carte((i+1)%w->nb_joueur, "Pretre");
                else if(liste_joueur[i]->getCarteMd()->affiche() == "Baron") w->ajouter_carte((i+1)%w->nb_joueur, "Baron");
                else if(liste_joueur[i]->getCarteMd()->affiche() == "Servante") w->ajouter_carte((i+1)%w->nb_joueur, "Servante");
                else if(liste_joueur[i]->getCarteMd()->affiche() == "Prince") w->ajouter_carte((i+1)%w->nb_joueur, "Prince");
                else if(liste_joueur[i]->getCarteMd()->affiche() == "Roi") w->ajouter_carte((i+1)%w->nb_joueur, "Roi");
                else if(liste_joueur[i]->getCarteMd()->affiche() == "Comtesse") w->ajouter_carte((i+1)%w->nb_joueur, "Comtesse");
                else if(liste_joueur[i]->getCarteMd()->affiche() == "Princesse") w->ajouter_carte((i+1)%w->nb_joueur, "Princesse");
            }
        }

        index_joueur_actuel = 0;

        liste_joueur[index_joueur_actuel%w->nb_joueur]->setProtege(false);

        Carte* tmp = liste_joueur[index_joueur_actuel%w->nb_joueur]->piocher();
        w->changer_nombre_carte(jeu->getNbCarte());

        if(tmp != nullptr)
        {
            if(tmp->affiche() == "Garde") w->ajouter_carte((index_joueur_actuel+1)%w->nb_joueur, "Garde");
            else if(tmp->affiche() == "Pretre") w->ajouter_carte((index_joueur_actuel+1)%w->nb_joueur, "Pretre");
            else if(tmp->affiche() == "Baron") w->ajouter_carte((index_joueur_actuel+1)%w->nb_joueur, "Baron");
            else if(tmp->affiche() == "Servante") w->ajouter_carte((index_joueur_actuel+1)%w->nb_joueur, "Servante");
            else if(tmp->affiche() == "Prince") w->ajouter_carte((index_joueur_actuel+1)%w->nb_joueur, "Prince");
            else if(tmp->affiche() == "Roi") w->ajouter_carte((index_joueur_actuel+1)%w->nb_joueur, "Roi");
            else if(tmp->affiche() == "Comtesse") w->ajouter_carte((index_joueur_actuel+1)%w->nb_joueur, "Comtesse");
            else if(tmp->affiche() == "Princesse") w->ajouter_carte((index_joueur_actuel+1)%w->nb_joueur, "Princesse");
        }

         w->set_index_joueur((index_joueur_actuel+1)%w->nb_joueur);

        /*
        Presentation* p = this;

        //ThreadModifie* t;
        //t->lancerThread((void*)Presentation::boucle_de_jeu, p);

        pthread_create(0, NULL, (void *(*)(void*))Presentation::boucle_de_jeu, NULL);

        //QObject::connect(p, SIGNAL(sign_ajouter_carte(int, char*)), w, SLOT(ajouter_carte(int, char*)));
        //QObject::connect(t, SIGNAL(sign_joueur_protege(int, bool)), w, SLOT(set_joueurProteger(int, bool)));
        //QObject::connect(p, SIGNAL(sign_set_index_joueur(int)), w, SLOT(set_index_joueur(int)));
        */
    }
    else if(strcmp(instructions[0], "trn") == 0)
    {
        w->activer_fin_de_tour(false);
        if(!jeu->checkMancheFinis())
        {
            jeu->nextTour();

            do{
                index_joueur_actuel++;
            }while(!liste_joueur[index_joueur_actuel%w->nb_joueur]->estVivant());

            w->set_index_joueur((index_joueur_actuel+1)%w->nb_joueur);

            Carte* tmp = liste_joueur[index_joueur_actuel%w->nb_joueur]->piocher();
            w->changer_nombre_carte(jeu->getNbCarte());
            for(unsigned int i = 0; i < liste_joueur.size(); i++)
            {
                w->vider_main((i+1)%w->nb_joueur);
                ajouter_main(i);
            }

            liste_joueur[index_joueur_actuel%w->nb_joueur]->setProtege(false);
            w->set_joueur_protege((index_joueur_actuel+1)%w->nb_joueur, false);

        }
        else
        {
            std::vector<Joueur*> gagnant_manche = jeu->mancheFinis();
            jeu->refresh(gagnant_manche);

            Joueur* gagnant = nullptr;
            for(unsigned int i = 0; i < liste_joueur.size(); i++)
            {
                if(liste_joueur[i]->getScore() >= jeu->nbPointGagner())
                {
                    gagnant = liste_joueur[i];
                }
            }

            if(gagnant != nullptr)
            {
                w->fin_de_partie((char*)gagnant->getNom().c_str());
                liste_joueur.clear();
                jeu->~Jeu();
            }
            else
            {
                /*char* annonce = "";

                strcpy(annonce, gagnant_manche[0]->getNom().c_str());

                for(unsigned int i = 1; i < gagnant_manche.size(); i++)
                {
                    strcat(annonce, ", ");
                    strcat(annonce, gagnant_manche[i]->getNom().c_str());
                }

                for(unsigned int i = 0; i < gagnant_manche.size(); i++)
                {
                    for(unsigned int j = 0; j < liste_joueur.size(); j++)
                    {
                        if(liste_joueur[j] == gagnant_manche[i])
                            w->change_score(j+1, liste_joueur[j]->getScore());
                    }
                }

                if(gagnant_manche.size() > 1)strcat(annonce, " ont gagnés la manche!");
                else strcat(annonce, " à gagné la manche!");

                w->annoncer(annonce);*/

                for(unsigned int i = 0; i < liste_joueur.size(); i++)
                {
                    w->vider_main((i+1)%w->nb_joueur);
                    w->vider_defausse((i+1)%w->nb_joueur);
                }

                index_joueur_actuel = 0;

                liste_joueur[index_joueur_actuel%w->nb_joueur]->piocher();
               // w->changer_nombre_carte(jeu->getNbCarte());

                w->set_index_joueur((index_joueur_actuel+1)%w->nb_joueur);

                for(unsigned int i = 0; i < liste_joueur.size(); i++)
                {
                    ajouter_main(i);
                }


            }
        }

    }
    else if(strcmp(instructions[0], "act") == 0)
    {
        char rep;

        int ret;

        moche:

        rep = instructions[2][0];

        type_carte carte;
        Carte* carte_cible;

        if(liste_joueur[(instructions[3][0]-1)%w->nb_joueur]->getCarteMg() != nullptr && rep != '1')
            carte_cible = liste_joueur[(instructions[3][0]-1)%w->nb_joueur]->getCarteMg();
        else if(liste_joueur[(instructions[3][0]-1)%w->nb_joueur]->getCarteMd() != nullptr)
            carte_cible = liste_joueur[(instructions[3][0]-1)%w->nb_joueur]->getCarteMd();

        if(rep == '1')
        {
            carte = liste_joueur[index_joueur_actuel%w->nb_joueur]->getCarteMg()->getType();

            if(carte == GARDE)
            {
                std::string str(instructions[4]);

                Carte* car = Carte::getTypeFromString(str);

                ret = liste_joueur[index_joueur_actuel%w->nb_joueur]->jouerCarteMg(liste_joueur[(instructions[3][0]-1)%w->nb_joueur],car);

            }
            else
                ret = liste_joueur[index_joueur_actuel%w->nb_joueur]->jouerCarteMg(liste_joueur[(instructions[3][0]-1)%w->nb_joueur]);
            if(ret == OK)
            {
                w->jeter_carte((index_joueur_actuel+1)%w->nb_joueur, 1, true);
            }

        }
        else
        {

            carte = liste_joueur[index_joueur_actuel%w->nb_joueur]->getCarteMd()->getType();

            if(carte == GARDE)
            {
                std::string str(instructions[4]);

                Carte* car = Carte::getTypeFromString(str);

                ret = liste_joueur[index_joueur_actuel%w->nb_joueur]->jouerCarteMd(liste_joueur[(instructions[3][0]-1)%w->nb_joueur],car);
            }
            else
                ret = liste_joueur[index_joueur_actuel%w->nb_joueur]->jouerCarteMd(liste_joueur[(instructions[3][0]-1)%w->nb_joueur]);
            if(ret == OK)
            {
                 w->jeter_carte((index_joueur_actuel+1)%w->nb_joueur, 2, true);
            }
        }

        if(ret != OK)
        {
            switch(ret) {
                case COMT:
                    //TODO afficher message
                    break;
                case DEAD:
                    //TODO afficher message
                    break;
                case PROT:
                    //TODO afficher message
                    break;
            }
            goto moche;
        }

        w->activer_fin_de_tour(true);

        for(unsigned int i = 0; i < liste_joueur.size(); i++)
        {
            w->vider_main((i+1)%w->nb_joueur);
            ajouter_main(i);
        }

        if(ret == OK)
        {
            w->set_joueur_protege((index_joueur_actuel+1)%w->nb_joueur, liste_joueur[index_joueur_actuel%w->nb_joueur]->estProtege());
            if(carte == PRETRE)
            {
                w->afficher_main((instructions[3][0])%w->nb_joueur);
            }
            else if(carte == PRINCE)
                w->jeter_carte((instructions[3][0])%w->nb_joueur, (char*)carte_cible->affiche().c_str()); //erreur de segmentation

        }
    }

}

void Presentation::ajouter_main(int i)
{
    if(liste_joueur[i]->getCarteMg() != nullptr)
    {
        if(liste_joueur[i]->getCarteMg()->affiche() == "Garde") w->ajouter_carte((i+1)%w->nb_joueur, "Garde");
        else if(liste_joueur[i]->getCarteMg()->affiche() == "Pretre") w->ajouter_carte((i+1)%w->nb_joueur, "Pretre");
        else if(liste_joueur[i]->getCarteMg()->affiche() == "Baron") w->ajouter_carte((i+1)%w->nb_joueur, "Baron");
        else if(liste_joueur[i]->getCarteMg()->affiche() == "Servante") w->ajouter_carte((i+1)%w->nb_joueur, "Servante");
        else if(liste_joueur[i]->getCarteMg()->affiche() == "Prince") w->ajouter_carte((i+1)%w->nb_joueur, "Prince");
        else if(liste_joueur[i]->getCarteMg()->affiche() == "Roi") w->ajouter_carte((i+1)%w->nb_joueur, "Roi");
        else if(liste_joueur[i]->getCarteMg()->affiche() == "Comtesse") w->ajouter_carte((i+1)%w->nb_joueur, "Comtesse");
        else if(liste_joueur[i]->getCarteMg()->affiche() == "Princesse") w->ajouter_carte((i+1)%w->nb_joueur, "Princesse");
    }
    if(liste_joueur[i]->getCarteMd() != nullptr)
    {
        if(liste_joueur[i]->getCarteMd()->affiche() == "Garde") w->ajouter_carte((i+1)%w->nb_joueur, "Garde");
        else if(liste_joueur[i]->getCarteMd()->affiche() == "Pretre") w->ajouter_carte((i+1)%w->nb_joueur, "Pretre");
        else if(liste_joueur[i]->getCarteMd()->affiche() == "Baron") w->ajouter_carte((i+1)%w->nb_joueur, "Baron");
        else if(liste_joueur[i]->getCarteMd()->affiche() == "Servante") w->ajouter_carte((i+1)%w->nb_joueur, "Servante");
        else if(liste_joueur[i]->getCarteMd()->affiche() == "Prince") w->ajouter_carte((i+1)%w->nb_joueur, "Prince");
        else if(liste_joueur[i]->getCarteMd()->affiche() == "Roi") w->ajouter_carte((i+1)%w->nb_joueur, "Roi");
        else if(liste_joueur[i]->getCarteMd()->affiche() == "Comtesse") w->ajouter_carte((i+1)%w->nb_joueur, "Comtesse");
        else if(liste_joueur[i]->getCarteMd()->affiche() == "Princesse") w->ajouter_carte((i+1)%w->nb_joueur, "Princesse");
    }
}
