#include "serveur.h"

#include <sstream>
#include <iterator>
#include <unistd.h>

std::vector<Client*> Serveur::liste_clients;
std::vector<char*> Serveur::Serveur::instructions;
std::vector<Joueur*> Serveur::liste_joueurs;

Jeu* Serveur::jeu;

int Serveur::nb_max;
int Serveur::index_joueur_actuel;

int Serveur::socket_serveur;

bool Serveur::en_jeu;

Serveur::Serveur(int n)
{
    int yes = 1;

    Serveur::nb_max = n;

    Serveur::socket_serveur = socket(AF_INET, SOCK_STREAM, 0);

    memset(&adresse_serveur, 0, sizeof(sockaddr_in));

    adresse_serveur.sin_family = AF_INET;
    adresse_serveur.sin_addr.s_addr = INADDR_ANY;
    adresse_serveur.sin_port = htons(12345);

    setsockopt(Serveur::socket_serveur, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &yes, sizeof(int));

    if(bind(Serveur::socket_serveur, (struct sockaddr*)&adresse_serveur, sizeof(sockaddr_in)) < 0)
    {
        std::cerr << "Erreur lors du bind" << std::endl;
    }

    listen(Serveur::socket_serveur, 5);

    Serveur::en_jeu = false;
}

Serveur::~Serveur()
{
}

void Serveur::lancer_serveur()
{
    Client* c;

    socklen_t taille_client = sizeof(sockaddr_in);

    Serveur::liste_clients.clear();

    while(1)
    {
        c = new Client();

        c->set_socket(accept(socket_serveur, (struct sockaddr*)&adresse_client, &taille_client));

        if(c->get_socket() < 0)
        {
            std::cerr << "Erreur lors de l'acceptation du client";
        }
        else
        {

            if(Serveur::liste_clients.size() < Serveur::nb_max)
            {

                bool a = false;

                for(unsigned int i = 0; i <= Serveur::liste_clients.size(); i++)
                {
                    if(!a && !get_client_par_id(i))
                    {
                        a = true;
                        c->set_id(i);
                        liste_clients.insert(liste_clients.begin() + i, c);
                    }
                }

                if(a)
                {
                    std::thread* t = new std::thread(Serveur::ecoute_client, c);
                }
                else
                {
                    std::cerr << "Pas de place";
                    c->~Client();
                }
            }
            else
            {
                std::cerr << "Nombre de joueur maximum atteint";
                c->~Client();
            }
        }
    }
}

void Serveur::eteindre_serveur()
{
    for(unsigned int i = 0; i < Serveur::liste_clients.size(); i++)
    {
        close(Serveur::liste_clients[i]->get_socket());
        std::cout << "Client " << Serveur::liste_clients[i]->get_id() << " déconnecté" << std::endl;
    }
    ::close(Serveur::socket_serveur);
    std::cout << "Serveur éteint" << std::endl;
}

void Serveur::ecoute_client(Client* c)
{
    char buffer[1024];
    char m[1024];
    char* mtmp = (char*)malloc(200);
    int n;
    bool en_route = true;

    while(1)
    {
        memset(buffer, 0, sizeof(buffer));
        memset(m, 0, sizeof(m));

        n = recv(c->get_socket(), buffer, sizeof(buffer), 0);

        if(n == 0)
        {
            std::cerr << "client déconnecté" << std::endl;
            close(c->get_socket());
            Serveur::liste_clients.erase(Serveur::liste_clients.begin() + c->get_id());

            strcpy(m, "eff|");
            strcat(m, (char*)to_string(c->get_id()).c_str());
            envoyer_tous(m);
            memset(m, 0, sizeof(m));

            if(Serveur::en_jeu)
            {
                Serveur::liste_joueurs.clear();
                Serveur::en_jeu = false;

                Serveur::jeu->~Jeu();

                strcpy(m, "dcx|");
                strcat(m, (char*)to_string(c->get_id()).c_str());
                envoyer_tous(m);
                memset(m, 0, sizeof(m));
            }

            break;
        }
        else if(n < 0)
        {
            std::cerr << "erreur dans la reception du message";
        }
        else
        {
            decomposer_message(buffer);

            if(strcmp(Serveur::instructions[0], "sht") == 0)
            {
                if(Serveur::en_jeu)
                {
                    Serveur::liste_joueurs.clear();
                    Serveur::en_jeu = false;
                    Serveur::jeu->~Jeu();
                }

                strcpy(m, "dcx|");
                strcat(m, (char*)to_string(c->get_id()).c_str());
                envoyer_tous(m);
                memset(m, 0, sizeof(m));

                for(Client* cli: Serveur::liste_clients)
                {
                    std::cerr << "client déconnecté" << std::endl;
                    close(cli->get_socket());
                }
                Serveur::liste_clients.clear();
                break;
            }
            else if(strcmp(Serveur::instructions[0], "dcx") == 0)
            {
                if(Serveur::en_jeu)
                {
                    Serveur::liste_joueurs.clear();
                    Serveur::en_jeu = false;
                    Serveur::jeu->~Jeu();
                }

                strcpy(m, "eff|");
                strcat(m, (char*)to_string(c->get_id()).c_str());
                envoyer_tous(m);
                memset(m, 0, sizeof(m));

                strcpy(m, "dcx|");
                strcat(m, (char*)to_string(c->get_id()).c_str());
                envoyer_a(c->get_id(), m);
                memset(m, 0, sizeof(m));

                std::cerr << "client déconnecté" << std::endl;
                close(c->get_socket());
                Serveur::liste_clients.erase(Serveur::liste_clients.begin() + c->get_id());

                break;
            }
            else if(strcmp(Serveur::instructions[0], "jon") == 0)
            {
                char* n = (char*)malloc(50);
                c->set_nom(Serveur::instructions[1]);

                int j = 0;
                for(Client* cli: Serveur::liste_clients)
                {
                    strcpy(m, "jon|");
                    strcat(m, (char*)to_string(cli->get_id()).c_str());
                    strcat(m, "|");

                    //strcat(m, cli->get_nom()); //la récupération du nom entré par le joueur ne marche pas

                    strcat(m, "player");
                    strcat(m, (char*)to_string(cli->get_id()).c_str());

                    if(j != c->get_id())
                    {
                        envoyer_a(c->get_id(), m);
                        memset(m, 0, sizeof(m));
                    }
                    else
                    {
                        envoyer_tous(m);
                        memset(m, 0, sizeof(m));

                        strcpy(m, "idl|");
                        sprintf(mtmp, "%d", c->get_id());
                        strcat(m, mtmp);
                        strcat(m, "|");
                        sprintf(mtmp, "%d", Serveur::nb_max);
                        strcat(m, mtmp);
                        envoyer_a(c->get_id(), m);
                        memset(m, 0, sizeof(m));
                    }

                    j++;
                }
            }
            else if(strcmp(Serveur::instructions[0], "str") == 0 && c->get_id() == 0 && Serveur::liste_clients.size() == Serveur::nb_max)
            {
                Serveur::en_jeu = true;

                Joueur* j1 = new Joueur(std::string(Serveur::instructions[1]));
                Joueur* j2 = new Joueur(std::string(Serveur::instructions[2]));
                Joueur* j3;
                Joueur* j4;

                std::cerr << Serveur::nb_max << std::endl;

                Serveur::liste_joueurs.push_back(j1);
                Serveur::liste_joueurs.push_back(j2);

                if(Serveur::nb_max >= 3)
                {
                    j3 = new Joueur(std::string(Serveur::instructions[3]));
                    Serveur::liste_joueurs.push_back(j3);
                }
                if(Serveur::nb_max >= 4)
                {
                    j4 = new Joueur(std::string(Serveur::instructions[4]));
                    Serveur::liste_joueurs.push_back(j4);
                }

                Serveur::jeu = new Jeu(Serveur::liste_joueurs);

                j1->ajouterJeu(Serveur::jeu);
                j2->ajouterJeu(Serveur::jeu);
                if(Serveur::nb_max >= 3) j3->ajouterJeu(Serveur::jeu);
                if(Serveur::nb_max >= 4) j4->ajouterJeu(Serveur::jeu);

                Serveur::jeu->initialisation();

                index_joueur_actuel = 0;

                Serveur::liste_joueurs[index_joueur_actuel%Serveur::nb_max]->setProtege(false);

                Carte* tmp = Serveur::liste_joueurs[index_joueur_actuel%Serveur::nb_max]->piocher();

                //piocher carte
                strcpy(m, "crt|");
                sprintf(mtmp, "%d", Serveur::jeu->getNbCarte());
                strcat(m, mtmp);
                envoyer_tous(m);
                memset(m, 0, sizeof(m));

                //set index
                strcpy(m, "idx|");
                sprintf(mtmp, "%d", (index_joueur_actuel+1)%Serveur::nb_max);
                strcat(m, mtmp);
                envoyer_tous(m);
                memset(m, 0, sizeof(m));

                for(unsigned int i = 0; i < Serveur::liste_joueurs.size(); i++)
                {
                    Serveur::ajouter_main(i);
                }


            }
            else if(strcmp(Serveur::instructions[0], "trn") == 0)
            {
                //activer fin tour
                strcpy(m, "aft|false");
                envoyer_tous(m);
                memset(m, 0, sizeof(m));

                if(!Serveur::jeu->checkMancheFinis())
                {
                    Serveur::jeu->nextTour();

                    do{
                        index_joueur_actuel++;
                    }while(!Serveur::liste_joueurs[index_joueur_actuel%Serveur::nb_max]->estVivant());

                    //set index
                    strcpy(m, "idx|");
                    sprintf(mtmp, "%d", (index_joueur_actuel+1)%Serveur::nb_max);
                    strcat(m, mtmp);
                    envoyer_tous(m);
                    memset(m, 0, sizeof(m));

                    Carte* tmp = Serveur::liste_joueurs[index_joueur_actuel%Serveur::nb_max]->piocher();

                    //piocher carte
                    strcpy(m, "crt|");
                    sprintf(mtmp, "%d", Serveur::jeu->getNbCarte());
                    strcat(m, mtmp);
                    envoyer_tous(m);
                    memset(m, 0, sizeof(m));

                    for(unsigned int i = 0; i < Serveur::liste_joueurs.size(); i++)
                    {
                        //vider main
                        strcpy(m, "vdm|");
                        sprintf(mtmp, "%d", (i+1)%Serveur::nb_max);
                        strcat(m, mtmp);
                        envoyer_tous(m);
                        memset(m, 0, sizeof(m));

                        ajouter_main(i);
                    }

                    Serveur::liste_joueurs[index_joueur_actuel%Serveur::nb_max]->setProtege(false);

                    //set protege
                    strcpy(m, "prt|");
                    sprintf(mtmp, "%d", (index_joueur_actuel+1)%Serveur::nb_max);
                    strcat(m, mtmp);
                    strcat(m, "|");
                    strcat(m, "false");
                    envoyer_tous(m);
                    memset(m, 0, sizeof(m));

                }
                else
                {
                    std::vector<Joueur*> gagnant_manche = Serveur::jeu->mancheFinis();
                    Serveur::jeu->refresh(gagnant_manche);

                    Joueur* gagnant = nullptr;
                    for(unsigned int i = 0; i < Serveur::liste_joueurs.size(); i++)
                    {
                        if(Serveur::liste_joueurs[i]->getScore() >= Serveur::jeu->nbPointGagner())
                        {
                            gagnant = Serveur::liste_joueurs[i];
                        }
                    }

                    if(gagnant != nullptr)
                    {
                        //fin de partie
                        strcpy(m, "fpt|");
                        strcat(m, (char*)gagnant->getNom().c_str());
                        envoyer_tous(m);
                        memset(m, 0, sizeof(m));

                        Serveur::liste_joueurs.clear();
                        Serveur::jeu->~Jeu();
                    }
                    else
                    {
                        int k = 0;
                        for(Joueur* j: Serveur::liste_joueurs)
                        {
                            if(!j->estVivant())
                            {
                                //set protege
                                strcpy(m, "prt|");
                                sprintf(mtmp, "%d", (k+1)%Serveur::nb_max);
                                strcat(m, mtmp);
                                strcat(m, "|");
                                strcat(m, "false");
                                envoyer_tous(m);
                                memset(m, 0, sizeof(m));
                            }
                            k++;
                        }

                        index_joueur_actuel = Serveur::nb_max;

                        //set index
                        strcpy(m, "idx|");
                        sprintf(mtmp, "%d", (index_joueur_actuel+1)%Serveur::nb_max);
                        strcat(m, mtmp);
                        envoyer_tous(m);
                        memset(m, 0, sizeof(m));

                        char* nom_vainqueurs = (char*)malloc(200);

                        strcpy(nom_vainqueurs, (char*)gagnant_manche[0]->getNom().c_str());
                        for(unsigned int i = 1; i < gagnant_manche.size(); i++)
                        {
                            strcat(nom_vainqueurs, "\n");
                            strcat(nom_vainqueurs, (char*)gagnant_manche[i]->getNom().c_str());
                        }

                        char* score_joueurs  = (char*)malloc(220);
                        char* stmp = (char*)malloc(3);

                        strcpy(score_joueurs, "");
                        for(unsigned int i = 0; i < liste_joueurs.size(); i++)
                        {
                            strcat(score_joueurs, (char*)liste_joueurs[i]->getNom().c_str());
                            strcat(score_joueurs, "  -  ");
                            sprintf(stmp, "%d", liste_joueurs[i]->getScore());
                            strcat(score_joueurs, stmp);
                            if(i != liste_joueurs.size()-1)
                                strcat(score_joueurs, "\n");
                        }

                        strcpy(m, "mch|");
                        strcat(m, nom_vainqueurs);
                        strcat(m, "|");
                        strcat(m, score_joueurs);
                        envoyer_tous(m);
                        memset(m, 0, sizeof(m));

                        free(nom_vainqueurs);
                        free(score_joueurs);
                        free(stmp);

                        for(unsigned int i = 0; i < Serveur::liste_joueurs.size(); i++)
                        {
                            //vider main
                            strcpy(m, "vdm|");
                            sprintf(mtmp, "%d", (i+1)%Serveur::nb_max);
                            strcat(m, mtmp);
                            envoyer_tous(m);
                            memset(m, 0, sizeof(m));

                            //vider defausse
                            strcpy(m, "vdd|");
                            sprintf(mtmp, "%d", (i+1)%Serveur::nb_max);
                            strcat(m, mtmp);
                            envoyer_tous(m);
                            memset(m, 0, sizeof(m));

                            ajouter_main(i);
                        }

                        Serveur::liste_joueurs[index_joueur_actuel%Serveur::nb_max]->piocher();

                        //piocher carte
                        strcpy(m, "crt|");
                        sprintf(mtmp, "%d", Serveur::jeu->getNbCarte());
                        strcat(m, mtmp);
                        envoyer_tous(m);
                        memset(m, 0, sizeof(m));

                        for(unsigned int i = 0; i < Serveur::liste_joueurs.size(); i++)
                        {
                            ajouter_main(i);
                        }
                    }
                }

            }
            else if(strcmp(Serveur::instructions[0], "act") == 0)
            {
                if(c->get_id() == Serveur::index_joueur_actuel%Serveur::nb_max)
                {
                    char rep;

                    int ret;

                    rep = Serveur::instructions[2][0];

                    type_carte carte;
                    int carte_cible;

                    if((Serveur::instructions[3][0]-1)%Serveur::nb_max == index_joueur_actuel)
                    {
                        if(rep == 1)
                            carte_cible = 2;
                        else
                            carte_cible = 1;
                    }
                    else
                    {
                        if(Serveur::liste_joueurs[(Serveur::instructions[3][0]-1)%Serveur::nb_max]->getCarteMg() != nullptr)
                            carte_cible = 1;
                        else if(Serveur::liste_joueurs[(Serveur::instructions[3][0]-1)%Serveur::nb_max]->getCarteMd() != nullptr)
                            carte_cible = 2;
                    }

                    if(rep == '1')
                    {
                        carte = Serveur::liste_joueurs[index_joueur_actuel%Serveur::nb_max]->getCarteMg()->getType();

                        if(carte == GARDE)
                        {
                            std::string str(Serveur::instructions[4]);

                            Carte* car = Carte::getTypeFromString(str);

                            ret = Serveur::liste_joueurs[index_joueur_actuel%Serveur::nb_max]->jouerCarteMg(Serveur::liste_joueurs[(Serveur::instructions[3][0]-1)%Serveur::nb_max],car);

                        }
                        else
                            ret = Serveur::liste_joueurs[index_joueur_actuel%Serveur::nb_max]->jouerCarteMg(Serveur::liste_joueurs[(Serveur::instructions[3][0]-1)%Serveur::nb_max]);
                        if(ret == OK)
                        {
                            //jeter carte
                            strcpy(m, "jet|");
                            sprintf(mtmp, "%d", (index_joueur_actuel+1)%Serveur::nb_max);
                            strcat(m, mtmp);
                            strcat(m, "|1|true");
                            envoyer_tous(m);
                            memset(m, 0, sizeof(m));
                        }

                    }
                    else
                    {
                        carte = Serveur::liste_joueurs[index_joueur_actuel%Serveur::nb_max]->getCarteMd()->getType();

                        if(carte == GARDE)
                        {
                            std::string str(Serveur::instructions[4]);

                            Carte* car = Carte::getTypeFromString(str);

                            ret = Serveur::liste_joueurs[index_joueur_actuel%Serveur::nb_max]->jouerCarteMd(Serveur::liste_joueurs[(Serveur::instructions[3][0]-1)%Serveur::nb_max],car);
                        }
                        else
                            ret = Serveur::liste_joueurs[index_joueur_actuel%Serveur::nb_max]->jouerCarteMd(Serveur::liste_joueurs[(Serveur::instructions[3][0]-1)%Serveur::nb_max]);
                        if(ret == OK)
                        {
                            //jeter carte
                            strcpy(m, "jet|");
                            sprintf(mtmp, "%d", (index_joueur_actuel+1)%Serveur::nb_max);
                            strcat(m, mtmp);
                            strcat(m, "|2|true");
                            envoyer_tous(m);
                            memset(m, 0, sizeof(m));
                        }
                    }

                    //activer fin tour
                    strcpy(m, "aft|true");
                    envoyer_a(c->get_id(), m);
                    memset(m, 0, sizeof(m));

                    if(ret == OK)
                    {
                        int k = 0;
                        for(Joueur* j: Serveur::liste_joueurs)
                        {
                            if(!j->estVivant())
                            {
                                //set protege
                                strcpy(m, "prt|");
                                sprintf(mtmp, "%d", (k+1)%Serveur::nb_max);
                                strcat(m, mtmp);
                                strcat(m, "|");
                                strcat(m, "true");
                                envoyer_tous(m);
                                memset(m, 0, sizeof(m));
                            }
                            k++;
                        }


                        //set protege
                        strcpy(m, "prt|");
                        sprintf(mtmp, "%d", (index_joueur_actuel+1)%Serveur::nb_max);
                        strcat(m, mtmp);
                        strcat(m, "|");
                        if(Serveur::liste_joueurs[index_joueur_actuel%Serveur::nb_max]->estProtege()) strcat(m, "true");
                        else strcat(m, "false");
                        envoyer_tous(m);
                        memset(m, 0, sizeof(m));

                        if((carte == GARDE && Serveur::liste_joueurs[(Serveur::instructions[3][0]-1)%Serveur::nb_max]->getCarteMg() == nullptr && Serveur::liste_joueurs[(Serveur::instructions[3][0]-1)%Serveur::nb_max]->getCarteMd() == nullptr) || carte == PRINCE)
                        {
                            //jeter carte
                            strcpy(m, "jet|");
                            sprintf(mtmp, "%d", (Serveur::instructions[3][0])%Serveur::nb_max);
                            strcat(m, mtmp);
                            strcat(m, "|");
                            sprintf(mtmp, "%d", carte_cible);
                            strcat(m, mtmp);
                            strcat(m, "|true");
                            envoyer_tous(m);
                            memset(m, 0, sizeof(m));
                        }

                        for(unsigned int i = 0; i < Serveur::liste_joueurs.size(); i++)
                        {
                            //vider main
                            strcpy(m, "vdm|");
                            sprintf(mtmp, "%d", (i+1)%Serveur::nb_max);
                            strcat(m, mtmp);
                            envoyer_tous(m);
                            memset(m, 0, sizeof(m));

                            ajouter_main(i);
                        }

                        if(carte == PRETRE)
                        {
                            //afficher main
                            strcpy(m, "aff|");
                            sprintf(mtmp, "%d", (Serveur::instructions[3][0])%Serveur::nb_max);
                            strcat(m, mtmp);
                            strcat(m, "|");
                            sprintf(mtmp, "%d", carte_cible);
                            strcat(m, mtmp);
                            envoyer_a(c->get_id(), m);
                            memset(m, 0, sizeof(m));
                        }
                    }
                }
                else
                {
                    envoyer_a(c->get_id(), "pup|Message du jeu|Ce n'est pas à votre tour de jouer.");
                }
            }
        }
    }
}

void Serveur::ajouter_main(int i)
{
    char* n = (char*)malloc(50);
    char* mtmp = (char*)malloc(5);
    char* m = (char*)malloc(1024);
    if(Serveur::liste_joueurs[i]->getCarteMg() != nullptr)
    {
        if(Serveur::liste_joueurs[i]->getCarteMg()->affiche() == "Garde") strcpy(n, "Garde");
        else if(Serveur::liste_joueurs[i]->getCarteMg()->affiche() == "Pretre") strcpy(n, "Pretre");
        else if(Serveur::liste_joueurs[i]->getCarteMg()->affiche() == "Baron") strcpy(n, "Baron");
        else if(Serveur::liste_joueurs[i]->getCarteMg()->affiche() == "Servante") strcpy(n, "Servante");
        else if(Serveur::liste_joueurs[i]->getCarteMg()->affiche() == "Prince") strcpy(n, "Prince");
        else if(Serveur::liste_joueurs[i]->getCarteMg()->affiche() == "Roi") strcpy(n, "Roi");
        else if(Serveur::liste_joueurs[i]->getCarteMg()->affiche() == "Comtesse") strcpy(n, "Comtesse");
        else if(Serveur::liste_joueurs[i]->getCarteMg()->affiche() == "Princesse") strcpy(n, "Princesse");

        //ajouter main
        strcpy(m, "ajt|");
        sprintf(mtmp, "%d", (i+1)%Serveur::nb_max);
        strcat(m, mtmp);
        strcat(m, "|1|");
        strcat(m, n);
        envoyer_tous(m);
        memset(m, 0, sizeof(m));
    }
    if(Serveur::liste_joueurs[i]->getCarteMd() != nullptr)
    {
        if(Serveur::liste_joueurs[i]->getCarteMd()->affiche() == "Garde") strcpy(n, "Garde");
        else if(Serveur::liste_joueurs[i]->getCarteMd()->affiche() == "Pretre") strcpy(n, "Pretre");
        else if(Serveur::liste_joueurs[i]->getCarteMd()->affiche() == "Baron") strcpy(n, "Baron");
        else if(Serveur::liste_joueurs[i]->getCarteMd()->affiche() == "Servante") strcpy(n, "Servante");
        else if(Serveur::liste_joueurs[i]->getCarteMd()->affiche() == "Prince") strcpy(n, "Prince");
        else if(Serveur::liste_joueurs[i]->getCarteMd()->affiche() == "Roi") strcpy(n, "Roi");
        else if(Serveur::liste_joueurs[i]->getCarteMd()->affiche() == "Comtesse") strcpy(n, "Comtesse");
        else if(Serveur::liste_joueurs[i]->getCarteMd()->affiche() == "Princesse") strcpy(n, "Princesse");

        //ajouter main
        strcpy(m, "ajt|");
        sprintf(mtmp, "%d", (i+1)%Serveur::nb_max);
        strcat(m, mtmp);
        strcat(m, "|2|");
        strcat(m, n);
        envoyer_tous(m);
        memset(m, 0, sizeof(m));
    }
}

void Serveur::decomposer_message(char* m)
{
    Serveur::instructions.clear();

    char* token = strtok(m, "|");

    while(token != NULL)
    {
        Serveur::instructions.push_back(token);
        token = strtok(NULL, "|");
    }
}

void Serveur::envoyer_a(int i, char* m)
{
    send(Serveur::liste_clients[i]->get_socket(), m, strlen(m), 0);
    sleep(1/5);
}

void Serveur::envoyer_tous(char* m)
{
    for(unsigned int i = 0; i < Serveur::liste_clients.size(); i++)
    {
        if(liste_clients[i] != nullptr)
            send(Serveur::liste_clients[i]->get_socket(), m, strlen(m), 0);
    }
    sleep(1/5);
}

bool Serveur::get_client_par_id(int i)
{
    for(Client* c: Serveur::liste_clients)
    {
        if(c->get_id() == i)
            return true;
    }
    return false;
}
