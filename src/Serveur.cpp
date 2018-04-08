#include "Serveur.h"

#include <sstream>
#include <iterator>
#include <mutex>
#include <condition_variable>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

vector<Client> Serveur::clients;

int Serveur::nbJoueurMax = 2;
int Serveur::nbJoueurCo = 0;

vector<char*> Serveur::instructions;

int Serveur::ready = -1;
int enJeu = 0;
int Serveur::indexJoueurActuel = 0;

condition_variable cv;
mutex mtx;

condition_variable cvStart;
mutex mtxStart;

Serveur::Serveur()
{
    int yes = 1;

    socketServeur = socket(AF_INET, SOCK_STREAM, 0);
    memset(&adresseServeur, 0, sizeof(sockaddr_in));
    adresseServeur.sin_family = AF_INET;
    adresseServeur.sin_addr.s_addr = INADDR_ANY;
    adresseServeur.sin_port = htons(12345);

    setsockopt(socketServeur, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

    if(bind(socketServeur, (struct sockaddr*)&adresseServeur, sizeof(sockaddr_in)) < 0)
    {
        cerr << "Erreur lors du bind";
    }

    listen(socketServeur, 5);


}

Serveur::~Serveur()
{
    //dtor
}


void Serveur::accepterClient()
{
    Client* c;
    ThreadModifie* t;

    socklen_t tailleClient = sizeof(sockaddr_in);

    Serveur::ready = -1;

    unique_lock<mutex> lockStart(mtxStart);
    cvStart.notify_one();

    while(1){
        c = new Client();
        t = new ThreadModifie();

        c->socket = accept(socketServeur, (struct sockaddr*)&adresseClient, &tailleClient);

        if(c->socket < 0)
        {
            cerr << "Erreur lors de l'acceptation du client";
        }
        else
        {
            t->lancerThread((void*)Serveur::callBack, c);

            Serveur::nbJoueurCo++;
        }

        if(Serveur::nbJoueurMax == Serveur::nbJoueurCo)
        {
            while(Serveur::ready != 0)
                cvStart.wait(lockStart);

            lancerPartie();
        }
    }

}

void* Serveur::callBack(void* args)
{
    Client* c = (Client*)args;

    char buffer[256-25], message[256];
    char* m = new char[1024];
    char* i = new char[3];
    int index;
    int n;

    c->setId(Serveur::clients.size());
    sprintf(buffer, "Client n.%d", c->id);
    cout << "Ajout du nouveau client avec l'id " << c->id << endl;
    Serveur::clients.push_back(*c);

    sprintf(i, "%d", c->id + 1);

    strcpy(m, "Vous êtes le joueur ");
    strcat(m, i);
    strcat(m, "\n\n");
    envoyerA(c->id, m);
    while(1)
    {
        memset(buffer, 0, sizeof(buffer));
        n = recv(c->socket, buffer, sizeof(buffer), 0);

        if(n == 0)
        {
            close(c->socket);

            index = trouverIndexClient(c);
            Serveur::clients.erase(Serveur::clients.begin() + index);

            Serveur::nbJoueurCo--;

            break;
        }
        else if(n < 0)
        {
            cerr << "Erreur dans la reception du message";
        }
        else
        {
            snprintf(message, sizeof(message), "%s", buffer);

            decomposerMessage(message);



            if(strcmp(Serveur::instructions[0], "jon") == 0)
            {
                c->setNom(Serveur::instructions[1]);

                for(size_t j = 0; j < clients.size(); j++)
                {
                    strcpy(m, "jon|");
                    strcat(m, (char*)to_string(clients[j].id).c_str());
                    strcat(m, "|");
                    strcat(m, clients[j].nom);

                    if(j != c->id)
                    {
                        envoyerA(c->id, m);
                    }
                    else
                    {
                        envoyerATous(m);
                    }
                }

                if(Serveur::nbJoueurMax == Serveur::nbJoueurCo)
                {
                    Serveur::ready = 0;

                    unique_lock<mutex> lockStart(mtxStart);
                    cvStart.notify_one();
                    lockStart.unlock();
                }
            }
            else if(Serveur::indexJoueurActuel%Serveur::nbJoueurCo == trouverIndexClient(c))
            {
				//if(strcmp(Serveur::instructions[0], "act")) // action sur la partie (jouer une carte)

                Serveur::ready = 0;

                unique_lock<mutex> lock(mtx);
                cv.notify_one();
                lock.unlock();

            }
            else
            {
                strcpy(buffer, "\nCe n'est pas votre tour\n");
                envoyerA(c->id, buffer);
            }
        }
    }

    return 0;

}

void Serveur::decomposerMessage(string m)
{
    Serveur::instructions.clear();

    char *cstr = new char[1024];

    strcpy(cstr, m.c_str());

    char* token = strtok(cstr, "|");

    while(token != NULL)
    {
        Serveur::instructions.push_back(token);
        token = strtok(NULL, "|");
    }
}

int Serveur::trouverIndexClient(Client* c)
{
    for(size_t i = 0; i < clients.size(); i++)
    {
        if((Serveur::clients[i].id == c->id))
        {
            return (int)i;
        }
    }

    cerr << "Ce client n'existe pas" << endl;

    return -1;
}

void Serveur::envoyerATous(char* m)
{
    for(size_t i = 0; i < clients.size(); i++)
    {
        send(Serveur::clients[i].socket, m, strlen(m), 0);

    }
}

void Serveur::envoyerA(int i, char* m)
{
    send(Serveur::clients[i].socket, m, strlen(m), 0);
}

void Serveur::lancerPartie()
{
    char* buffer = new char[1024];
    char* indexJoueur = new char[3];

    Joueur *j1 = new Joueur(Serveur::clients[0].nom);
    Joueur *j2 = new Joueur(Serveur::clients[1].nom);

    std::vector<Joueur*> jrs;
    jrs.push_back(j1);
    jrs.push_back(j2);

    Jeu *j = new Jeu(jrs);

    j1->ajouterJeu(j);
    j2->ajouterJeu(j);

    j->initialisation();

    std::vector<Joueur*> joueurs;
    joueurs.push_back(j1);
    joueurs.push_back(j2);

    unique_lock<mutex> lock(mtx);
    cv.notify_one();

	char rep;
	Serveur::indexJoueurActuel = 0;

	while(!j->finis())
	{
        sprintf(indexJoueur, "%d", (Serveur::indexJoueurActuel + 1)%Serveur::nbJoueurCo);

		joueurs[Serveur::indexJoueurActuel%2]->setProtege(false);
		joueurs[Serveur::indexJoueurActuel%2]->piocher();

        strcpy(buffer, "_____________________TOUR_JOUEUR_");
		strcat(buffer, indexJoueur);
		strcat(buffer, "_____________________");
		envoyerATous(buffer);

        strcpy(buffer, "\nJoueur 1\n");
		envoyerATous(buffer);
        if(j1->getCarteMg() != nullptr)
        {
            strcpy(buffer, j1->getCarteMg()->affiche().c_str());
            strcat(buffer,"\n");
            envoyerATous(buffer);
        }
        if(j1->getCarteMd() != nullptr)
        {
            strcpy(buffer, j1->getCarteMd()->affiche().c_str());
            strcat(buffer,"\n");
            envoyerATous(buffer);
        }

        strcpy(buffer, "\nJoueur 2\n");
		envoyerATous(buffer);
		if(j2->getCarteMg() != nullptr)
		{
            strcpy(buffer, j2->getCarteMg()->affiche().c_str());
            strcat(buffer,"\n");
            envoyerATous(buffer);
        }
        if(j2->getCarteMd() != nullptr)
        {
            strcpy(buffer, j2->getCarteMd()->affiche().c_str());
            strcat(buffer,"\n");
            envoyerATous(buffer);
        }

		int ret;

		moche:

		Serveur::ready = -1;

		while(Serveur::ready != 0)
            cv.wait(lock);

		rep = Serveur::instructions[0][0];

		if(rep == '1')
		{
			if(joueurs[Serveur::indexJoueurActuel%2]->getCarteMg()->getType() == GARDE)
			{
				strcpy(buffer, "\nVeuillez entrez le nom de la carte que vous voulez comparer\n");
                Serveur::envoyerA(Serveur::indexJoueurActuel%2, buffer);

				Serveur::ready = -1;

                while(Serveur::ready != 0)
                    cv.wait(lock);

                std::string str(Serveur::instructions[0]);

				Carte* car = Carte::getTypeFromString(str);

				while(car == nullptr)
				{
                    strcpy(buffer, "\nVeuillez entrez le nom de la carte que vous voulez comparer\n");
                    Serveur::envoyerA(Serveur::indexJoueurActuel%2, buffer);

                    Serveur::ready = -1;

                    while(Serveur::ready != 0)
                        cv.wait(lock);

                    std::string str2(Serveur::instructions[0]);

					car = Carte::getTypeFromString(str2);
				}

				ret = joueurs[Serveur::indexJoueurActuel%2]->jouerCarteMg(joueurs[(Serveur::indexJoueurActuel+1)%2],car);
			}
			else
				ret = joueurs[Serveur::indexJoueurActuel%2]->jouerCarteMg(joueurs[(Serveur::indexJoueurActuel+1)%2]);
            strcpy(buffer, "\nLe joueur ");
            strcat(buffer, indexJoueur);
            strcat(buffer, " joue sa carte en main gauche\n");
            envoyerATous(buffer);
		}
		else
		{
			if(joueurs[Serveur::indexJoueurActuel%2]->getCarteMd()->getType() == GARDE)
            {
                strcpy(buffer, "\nVeuillez entrez le nom de la carte que vous voulez comparer\n");
                Serveur::envoyerA(Serveur::indexJoueurActuel%2, buffer);

                Serveur::ready = -1;

                while(Serveur::ready != 0)
                        cv.wait(lock);

                std::string str(Serveur::instructions[0]);

                Carte* car = Carte::getTypeFromString(str);

                while(car == nullptr)
                {
					strcpy(buffer, "\nVeuillez entrez le nom de la carte que vous voulez comparer\n");
					Serveur::envoyerA(Serveur::indexJoueurActuel%2, buffer);

					Serveur::ready = -1;

					while(Serveur::ready != 0)
							cv.wait(lock);

					std::string str2(Serveur::instructions[0]);

					car = Carte::getTypeFromString(str2);
                }

                ret = joueurs[Serveur::indexJoueurActuel%2]->jouerCarteMd(joueurs[(Serveur::indexJoueurActuel+1)%2],car);
            }
			else
				ret = joueurs[Serveur::indexJoueurActuel%2]->jouerCarteMd(joueurs[(Serveur::indexJoueurActuel+1)%2]);
            strcpy(buffer, "\nLe joueur ");
            strcat(buffer, indexJoueur);
            strcat(buffer, " joue sa carte en main droite\n");
            envoyerATous(buffer);
		}

		if(ret != OK)
		{
			switch(ret) {
				case COMT:
                    strcpy(buffer, "\nVous devez jouer la comtesse\n");
					envoyerA(Serveur::indexJoueurActuel, buffer);
					break;
				case DEAD:
                    strcpy(buffer, "\nLe joueur que vous visez n'est plus dans la partie\n");
					envoyerA(Serveur::indexJoueurActuel, buffer);
					break;
				case PROT:
                    strcpy(buffer, "\nVous devez jouer la comtesse\n");
					envoyerA(Serveur::indexJoueurActuel, buffer);
					break;
			}
			goto moche;
		}

		j->nextTour();
		Serveur::indexJoueurActuel++;
	}
}
