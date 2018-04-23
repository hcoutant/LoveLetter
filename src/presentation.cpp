#include "presentation.h"

#include <QDebug>
#include <QDir>
#include <QObject>
#include <QString>
#include <QTranslator>
#include <QFile>

#include <cstdint>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#include <thread>

int Presentation::en_route;

Presentation::Presentation()
{
    Presentation::en_route = 0;
}

int Presentation::lancer_fenetre(int argc, char *argv[])
{
    QApplication a(argc, argv);


    w = new MainWindow;

    CallBack* c = this;

    w->set_callBack(c);

    w->set_qApp(&a);

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

void Presentation::call(char* a)
{

    char* buffer = (char*)malloc(1024);
    strcpy(buffer, a);

    decomposer_action(a);

    connect(this, SIGNAL(sign_ajouter_carte(int,int,char*)), this, SLOT(ajouter_carte(int,int,char*)));
    connect(this, SIGNAL(sign_jeter_carte(int,int,bool)), this, SLOT(jeter_carte(int,int,bool)));
    connect(this, SIGNAL(sign_vider_main(int)), this, SLOT(vider_main(int)));
    connect(this, SIGNAL(sign_vider_defausse(int)), this, SLOT(vider_defausse(int)));
    connect(this, SIGNAL(sign_set_index_joueur(int)), this, SLOT(set_index_joueur(int)));
    connect(this, SIGNAL(sign_changer_nombre_carte(int)), this, SLOT(changer_nombre_carte(int)));
    connect(this, SIGNAL(sign_set_joueur_protege(int,bool)), this, SLOT(set_joueur_protege(int,bool)));
    connect(this, SIGNAL(sign_activer_fin_tour(bool)), this, SLOT(activer_fin_tour(bool)));
    connect(this, SIGNAL(sign_fin_partie(char*)), this, SLOT(fin_partie(char*)));
    connect(this, SIGNAL(sign_fin_manche(char*,char*)), this, SLOT(fin_manche(char*,char*)));
    connect(this, SIGNAL(sign_afficher_main(int,int)), this, SLOT(afficher_main(int,int)));
    connect(this, SIGNAL(sign_set_nb_joueur(int)), this, SLOT(set_nb_joueur(int)));
    connect(this, SIGNAL(sign_changer_widget(int)), this, SLOT(changer_widget(int)));
    connect(this, SIGNAL(sign_effacer_pseudo(int)), this, SLOT(effacer_pseudo(int)));
    connect(this, SIGNAL(sign_afficher_pop_up(int,char*,char*)), this, SLOT(afficher_pop_up(int,char*,char*)));

    if(w->est_local)
    {

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

            index_joueur_actuel = 0;

            liste_joueur[index_joueur_actuel%w->nb_joueur]->setProtege(false);

            Carte* tmp = liste_joueur[index_joueur_actuel%w->nb_joueur]->piocher();
            emit sign_changer_nombre_carte(jeu->getNbCarte());

            emit sign_set_index_joueur((index_joueur_actuel+1)%w->nb_joueur);

            for(unsigned int i = 0; i < liste_joueur.size(); i++)
            {
                ajouter_main(i);
            }
        }
        else if(strcmp(instructions[0], "trn") == 0)
        {
            emit sign_activer_fin_tour(false);

            if(!jeu->checkMancheFinis())
            {
                jeu->nextTour();

                do{
                    index_joueur_actuel++;
                }while(!liste_joueur[index_joueur_actuel%w->nb_joueur]->estVivant());

                emit sign_set_index_joueur((index_joueur_actuel+1)%w->nb_joueur);

                Carte* tmp = liste_joueur[index_joueur_actuel%w->nb_joueur]->piocher();
                emit sign_changer_nombre_carte(jeu->getNbCarte());
                for(unsigned int i = 0; i < liste_joueur.size(); i++)
                {
                    emit vider_main((i+1)%w->nb_joueur);
                    ajouter_main(i);
                }

                liste_joueur[index_joueur_actuel%w->nb_joueur]->setProtege(false);
                emit sign_set_joueur_protege((index_joueur_actuel+1)%w->nb_joueur, false);

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
                    int k = 0;
                    for(Joueur* j: liste_joueur)
                    {
                        if(!j->estVivant())
                        {
                            emit sign_set_joueur_protege((k+1)%w->nb_joueur, false);
                        }
                        k++;
                    }

                    index_joueur_actuel = w->nb_joueur;

                    emit sign_set_index_joueur((index_joueur_actuel+1)%w->nb_joueur);

                    char* nom_vainqueurs = (char*)malloc(200);

		    if(gagnant_manche.size() > 0)
		    {
                    	strcpy(nom_vainqueurs, (char*)gagnant_manche[0]->getNom().c_str());
	                for(unsigned int i = 1; i < gagnant_manche.size(); i++)
	                {
	                    strcat(nom_vainqueurs, "\n");
	                    strcat(nom_vainqueurs, (char*)gagnant_manche[i]->getNom().c_str());
	                }
		    }
		    else
		    {
			strcpy(nom_vainqueurs, "Erreur dans la récupération du nom des gagnants de la manche");
		    }

                    char* score_joueurs  = (char*)malloc(220);
                    char* stmp = (char*)malloc(3);

                    strcpy(score_joueurs, "");
                    for(unsigned int i = 0; i < liste_joueur.size(); i++)
                    {
                        strcat(score_joueurs, (char*)liste_joueur[i]->getNom().c_str());
                        strcat(score_joueurs, "  -  ");
                        sprintf(stmp, "%d", liste_joueur[i]->getScore());
                        strcat(score_joueurs, stmp);
                        if(i != liste_joueur.size()-1)
                            strcat(score_joueurs, "\n");
                    }

                    emit sign_fin_manche(nom_vainqueurs, score_joueurs);

                    free(nom_vainqueurs);
                    free(score_joueurs);
                    free(stmp);

                    for(unsigned int i = 0; i < liste_joueur.size(); i++)
                    {
                        emit vider_main((i+1)%w->nb_joueur);
                        emit vider_defausse((i+1)%w->nb_joueur);
                    }

                    liste_joueur[index_joueur_actuel%w->nb_joueur]->piocher();
                    emit sign_changer_nombre_carte(jeu->getNbCarte());

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

            rep = instructions[2][0];

            type_carte carte;
            int carte_cible;
	

            if((instructions[3][0]-1)%w->nb_joueur == index_joueur_actuel)
            {
                if(rep == 1)
                    carte_cible = 2;
                else
                    carte_cible = 1;
            }
            else
            {
                if(liste_joueur[(instructions[3][0]-1)%w->nb_joueur]->getCarteMg() != nullptr)
                    carte_cible = 1;
                else if(liste_joueur[(instructions[3][0]-1)%w->nb_joueur]->getCarteMd() != nullptr)
                    carte_cible = 2;
            }

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
                    emit sign_jeter_carte((index_joueur_actuel+1)%w->nb_joueur, 1, true);
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
                    emit sign_jeter_carte((index_joueur_actuel+1)%w->nb_joueur, 2, true);
                }
            }

            emit sign_activer_fin_tour(true);


            if(ret == OK)
            {
                int k = 0;
                for(Joueur* j: liste_joueur)
                {
                    if(!j->estVivant())
                    {
                        emit sign_set_joueur_protege((k+1)%w->nb_joueur, true);
                    }
                    k++;
                }

                emit sign_set_joueur_protege((index_joueur_actuel+1)%w->nb_joueur, liste_joueur[index_joueur_actuel%w->nb_joueur]->estProtege());

                if(carte == GARDE && liste_joueur[(instructions[3][0]-1)%w->nb_joueur]->getCarteMg() == nullptr && liste_joueur[(instructions[3][0]-1)%w->nb_joueur]->getCarteMd() == nullptr)
                    emit sign_jeter_carte((instructions[3][0])%w->nb_joueur, carte_cible, true);
                else if(carte == PRINCE)
                    emit sign_jeter_carte((instructions[3][0])%w->nb_joueur, carte_cible, true);

                for(unsigned int i = 0; i < liste_joueur.size(); i++)
                {
                    emit vider_main((i+1)%w->nb_joueur);
                    ajouter_main(i);
                }

                if(carte == PRETRE)
                    emit afficher_main((instructions[3][0])%w->nb_joueur, carte_cible);

            }

        }
    }
    else //jeu en ligne
    {

        connect(this, SIGNAL(sign_ajouter_joueur(int,char*)), this, SLOT(ajouter_joueur(int,char*)));
        connect(this, SIGNAL(sign_set_index_local(int)), this, SLOT(set_index_local(int)));

        if(strcmp(instructions[0], "hst") == 0)
        {
            if(serveur != nullptr)
                serveur->~Serveur();
            serveur = new Serveur(atoi(instructions[1]));

            thread_serveur = new std::thread(lancer_serveur, serveur);

            sleep(1);

            socklen_t adr_taille = sizeof(struct sockaddr_in);

            struct sockaddr_in adresse;
            adresse.sin_family = AF_INET;
            adresse.sin_port = htons(12345);

            inet_pton(AF_INET, "127.0.0.1", &adresse.sin_addr);
            socket_client = socket(AF_INET, SOCK_STREAM, 0);

            if(::connect(socket_client, (struct sockaddr*)&adresse, adr_taille) < 0)
            {
                std::cerr << "Connexion au serveur échouée";
            }
            else
            {
                thread_ecoute = new std::thread(lancer_ecoute, this);

                w->change_affichage(3);

                char m[1024];
                strcpy(m, "jon|");
                strcat(m, instructions[2]);
                envoyer_message(m);
            }

        }
        else if(strcmp(instructions[0], "cnx") == 0)
        {
            socklen_t adr_taille = sizeof(struct sockaddr_in);

            struct sockaddr_in adresse;
            adresse.sin_family = AF_INET;
            adresse.sin_port = htons(12345);

            inet_pton(AF_INET, instructions[1], &adresse.sin_addr);
            socket_client = socket(AF_INET, SOCK_STREAM, 0);

            if(::connect(socket_client, (struct sockaddr*)&adresse, adr_taille) < 0)
            {
                std::cerr << "Connexion au serveur échouée";
            }
            else
            {
                thread_ecoute = new std::thread(lancer_ecoute, this);

                w->change_affichage(3);

                char m[1024];
                strcpy(m, "jon|");
                strcat(m, instructions[2]);
                envoyer_message(m);
            }
        }
        else if(strcmp(instructions[0], "sht") == 0)
        {
            envoyer_message(buffer);
        }
        else if(strcmp(instructions[0], "dcx") == 0)
        {
            envoyer_message(buffer);
        }
        else
        {
            envoyer_message(buffer);
        }
    }

}

void Presentation::ajouter_main(int i)
{
    if(liste_joueur[i]->getCarteMg() != nullptr)
    {
        if(liste_joueur[i]->getCarteMg()->affiche() == "Garde") emit sign_ajouter_carte((i+1)%w->nb_joueur, 1, "Garde");
        else if(liste_joueur[i]->getCarteMg()->affiche() == "Pretre") emit sign_ajouter_carte((i+1)%w->nb_joueur, 1, "Pretre");
        else if(liste_joueur[i]->getCarteMg()->affiche() == "Baron") emit sign_ajouter_carte((i+1)%w->nb_joueur, 1, "Baron");
        else if(liste_joueur[i]->getCarteMg()->affiche() == "Servante") emit sign_ajouter_carte((i+1)%w->nb_joueur, 1, "Servante");
        else if(liste_joueur[i]->getCarteMg()->affiche() == "Prince") emit sign_ajouter_carte((i+1)%w->nb_joueur, 1, "Prince");
        else if(liste_joueur[i]->getCarteMg()->affiche() == "Roi") emit sign_ajouter_carte((i+1)%w->nb_joueur, 1, "Roi");
        else if(liste_joueur[i]->getCarteMg()->affiche() == "Comtesse") emit sign_ajouter_carte((i+1)%w->nb_joueur, 1, "Comtesse");
        else if(liste_joueur[i]->getCarteMg()->affiche() == "Princesse") emit sign_ajouter_carte((i+1)%w->nb_joueur, 1, "Princesse");
    }
    if(liste_joueur[i]->getCarteMd() != nullptr)
    {
        if(liste_joueur[i]->getCarteMd()->affiche() == "Garde") emit sign_ajouter_carte((i+1)%w->nb_joueur, 2, "Garde");
        else if(liste_joueur[i]->getCarteMd()->affiche() == "Pretre") emit sign_ajouter_carte((i+1)%w->nb_joueur, 2, "Pretre");
        else if(liste_joueur[i]->getCarteMd()->affiche() == "Baron") emit sign_ajouter_carte((i+1)%w->nb_joueur, 2, "Baron");
        else if(liste_joueur[i]->getCarteMd()->affiche() == "Servante") emit sign_ajouter_carte((i+1)%w->nb_joueur, 2, "Servante");
        else if(liste_joueur[i]->getCarteMd()->affiche() == "Prince") emit sign_ajouter_carte((i+1)%w->nb_joueur, 2, "Prince");
        else if(liste_joueur[i]->getCarteMd()->affiche() == "Roi") emit sign_ajouter_carte((i+1)%w->nb_joueur, 2, "Roi");
        else if(liste_joueur[i]->getCarteMd()->affiche() == "Comtesse") emit sign_ajouter_carte((i+1)%w->nb_joueur, 2, "Comtesse");
        else if(liste_joueur[i]->getCarteMd()->affiche() == "Princesse") emit sign_ajouter_carte((i+1)%w->nb_joueur, 2, "Princesse");
    }
}



//Slots



void Presentation::ajouter_carte(int i, int g, char* n)
{
    w->ajouter_carte(i, g, n);
}

void Presentation::jeter_carte(int i, int g, bool d)
{
    w->jeter_carte(i, g, d);
}

void Presentation::vider_main(int i)
{
    w->vider_main(i);
}

void Presentation::vider_defausse(int i)
{
    w->vider_defausse(i);
}

void Presentation::set_index_joueur(int i)
{
    w->set_index_joueur(i);
}

void Presentation::changer_nombre_carte(int i)
{
    w->changer_nombre_carte(i);
}

void Presentation::set_joueur_protege(int i, bool p)
{
    w->set_joueur_protege(i, p);
}

void Presentation::activer_fin_tour(bool f)
{
    w->activer_fin_de_tour(f);
}

void Presentation::fin_partie(char* n)
{
    w->fin_de_partie(n);
}

void Presentation::fin_manche(char* v, char* s)
{
    w->set_vainqueur_manche(v, s);
}

void Presentation::afficher_main(int i, int c)
{
    w->afficher_main(i, c);
}

void Presentation::ajouter_joueur(int i, char* n)
{
    w->ajouter_joueur(i, n);
}

void Presentation::set_index_local(int i)
{
    w->set_index_local(i);
}

void Presentation::set_nb_joueur(int i)
{
    w->set_nb_joueur(i);
}

void Presentation::changer_widget(int i)
{
    w->changer_widget(i);
}

void Presentation::effacer_pseudo(int i)
{
    w->effacer_pseudo(i);
}

void Presentation::afficher_pop_up(int i, char* t, char* n)
{
    w->afficher_pop_up(i, t, n);
}



//Partie reseau



void Presentation::envoyer_message(char* m)
{
    send(socket_client, m, strlen(m), 0);
}

void Presentation::lancer_serveur(Serveur* s)
{
    std::cout << "Serveur lancé" << std::endl;
    s->lancer_serveur();
}

void Presentation::lancer_ecoute(Presentation* p)
{
    int n;

    std::vector<char*> instructions_serveur;

    char buffer[1024];
    while(1){

        memset(buffer, 0, sizeof(buffer));

        n = recv(p->socket_client, buffer, sizeof(buffer), 0);

        if(n == 0)
        {
            std::cerr << "Serveur déconnecté" << std::endl;
            close(p->socket_client);
            emit p->sign_changer_widget(8);
            break;
        }
        else if(n < 0)
        {
            std::cerr << "Erreur dans la réception du message" << std::endl;
        }
        else
        {
            instructions_serveur.clear();

            char* token = strtok(buffer, "|");

            while(token != NULL)
            {
                instructions_serveur.push_back(token);
                token = strtok(NULL, "|");
            }

            if(strcmp(instructions_serveur[0], "jon") == 0) // joueur rejoint la partie
            {
                char* n = (char*)malloc(200);
                strcpy(n,instructions_serveur[2]);
                emit p->sign_ajouter_joueur(atoi(instructions_serveur[1]), n);
            }
            else if(strcmp(instructions_serveur[0], "idl") == 0)
            {
                emit p->sign_set_index_local(atoi(instructions_serveur[1]));
                emit p->sign_set_nb_joueur(atoi(instructions_serveur[2]));
            }
            else if(strcmp(instructions_serveur[0], "idx") == 0) // changer joueur
            {
                emit p->sign_set_index_joueur(atoi(instructions_serveur[1]));
            }
            else if(strcmp(instructions_serveur[0], "crt") == 0) // actualiser nombre carte pile
            {
                emit p->sign_changer_nombre_carte(atoi(instructions_serveur[1]));
            }
            else if(strcmp(instructions_serveur[0], "ajt") == 0) // actualiser main
            {
                char* n = (char*)malloc(50);
                strcpy(n, instructions_serveur[3]);
                emit p->sign_ajouter_carte(atoi(instructions_serveur[1]), atoi(instructions_serveur[2]), n);
            }
            else if(strcmp(instructions_serveur[0], "aft") == 0) // jouer carte
            {
                if(strcmp(instructions_serveur[1], "true") == 0)
                    emit p->sign_activer_fin_tour(true);
                else
                    emit p->sign_activer_fin_tour(false);
            }
            else if(strcmp(instructions_serveur[0], "vdm") == 0) // vider main
            {
                emit p->sign_vider_main(atoi(instructions_serveur[1]));
            }
            else if(strcmp(instructions_serveur[0], "vdd") == 0) // vider defausse
            {
                emit p->sign_vider_defausse(atoi(instructions_serveur[1]));
            }
            else if(strcmp(instructions_serveur[0], "jet") == 0) // jeter carte
            {
                bool d;
                if(strcmp(instructions_serveur[3], "true") == 0)
                    d = true;
                else
                    d = false;
                emit p->sign_jeter_carte(atoi(instructions_serveur[1]), atoi(instructions_serveur[2]), d);
            }
            else if(strcmp(instructions_serveur[0], "aff") == 0) // afficher main joueur
            {
                emit p->sign_afficher_main(atoi(instructions_serveur[1]), atoi(instructions_serveur[2]));
            }
            else if(strcmp(instructions_serveur[0], "prt") == 0) // set joueur protégé
            {
                bool d;
                if(strcmp(instructions_serveur[2], "true") == 0)
                    d = true;
                else
                    d = false;
                emit p->sign_set_joueur_protege(atoi(instructions_serveur[1]), d);
            }
            else if(strcmp(instructions_serveur[0], "mch") == 0) // fin de la manche
            {
                char* v = (char*)malloc(200);
                char* s = (char*)malloc(220);

                strcpy(v, instructions_serveur[1]);
                strcpy(s, instructions_serveur[2]);

                emit p->sign_fin_manche(v, s);
            }
            else if(strcmp(instructions_serveur[0], "fpt") == 0) // fin de la partie
            {
                emit p->sign_fin_partie(instructions_serveur[1]);
            }
            else if(strcmp(instructions_serveur[0], "pup") == 0) // afficher pop up
            {
                char* t = (char*)malloc(200);
                char* n = (char*)malloc(200);

                strcpy(t, instructions_serveur[2]);
                strcpy(n, instructions_serveur[3]);

                emit p->sign_afficher_pop_up(atoi(instructions_serveur[1]), t, n);
            }
            else if(strcmp(instructions_serveur[0], "eff") == 0) // retirer joueur
            {
                emit p->sign_effacer_pseudo(atoi(instructions_serveur[1]));
            }
            else if(strcmp(instructions_serveur[0], "dcx") == 0) // déconnexion
            {
                emit p->sign_changer_widget(8);
                std::cout << "deconnexion du serveur" << std::endl;
                close(p->socket_client);
                break;
            }
        }
    }
}
