#include <iostream>

#include <cstdint>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#include "ThreadModifie.h"
#include "Serveur.h"

using namespace std;

int enRoute = 0;
vector<char*> instructions;
vector<char*> joueurs;

void decomposerMessage(char* m)
{
    instructions.clear();

    char* token = strtok(m, "|");

    while(token != NULL)
    {
        instructions.push_back(token);
        token = strtok(NULL, "|");
    }
}

void envoyerMessage(int s, const char* m)
{
	send(s, m, strlen(m), 0);
}

void callBack(void* args)
{
    int n;
    intptr_t socket = (intptr_t)args;

    char buffer[1024];
    while(1){
        memset(buffer, 0, sizeof(buffer));
        n = recv(socket, buffer, sizeof(buffer), 0);
        if(n == 0)
        {
            enRoute = -1;
            cout << endl << "Serveur déconnecté - arrêt du programme" << endl;
            exit(0);
        }
        else if(n < 0)
        {
            cout << endl << "Erreur dans la réception du message" << endl;
        }
        else
        {

			decomposerMessage(buffer);

			if(strcmp(instructions[0], "jon") == 0) // joueur rejoint la partie
			{
				//TODO ajouter le joueur instructions[1] dans la liste des joueurs de la partie avec le pseudo instructions[2];
			}
			else if(strcmp(instructions[0], "drw") == 0) // piocher
			{
				//TODO ajouter la carte instructions[2] au joueur instructions[1];
			}
			else if(strcmp(instructions[0], "dsc") == 0) // jouer une carte
			{
				//TODO enlever la carte instructions[2] au joueur instructions[1];
			}
			else if(strcmp(instructions[0], "prt") == 0) // joueur protégé
			{
				//TODO afficher "le joueur instructions[1] est protégé";
			}
			else if(strcmp(instructions[0], "eli") == 0) // joueur éliminé
			{
				//TODO afficher "le joueur instructions[1] est éliminé de la manche";
			}
			else if(strcmp(instructions[0], "dpl") == 0) // afficher un message
			{
				//TODO afficher le message instructions[1] à l'écran;
			}
			else if(strcmp(instructions[0], "shw") == 0) // afficher carte d'un joueur (Prêtre)
			{
				//TODO afficher la carte du joueur instructions[1];
			}
			else
			{
                printf("%s", instructions[0]);
			}

        }
    }
}

/*
lancer le programme dans un terminal et choisir serveur, 
puis lancer dans un deuxième terminal le joueur 1,
puis lancer dans un troisième terminal le joueur 2
*/

int main(void)
{
    cout << "Choisissez une option: " << endl << "1 pour serveur" << endl << "2 pour joueur" << endl;

    string choix;

    cin >> choix;

    if(choix == "1")
    {
        Serveur* s;
        s = new Serveur();

        s->accepterClient();
        
        cout << "Serveur lancé: en attente de connexion" << endl;
    }
    else if(choix == "2")
    {
        int sock;
        int connexion = -1;
        string ip;
        string buffer;
		string pseudo;

        socklen_t adr_taille = sizeof(struct sockaddr_in);

        struct sockaddr_in adresse;
        adresse.sin_family = AF_INET;
        adresse.sin_port = htons(12345);

        while(connexion != 0)
        {
            cout << endl << "ip du serveur: " << endl;
            cin >> ip;

			cout << endl << "entrer un pseudo: " << endl;
			cin >> pseudo;

            inet_pton(AF_INET, ip.c_str(), &adresse.sin_addr);

            sock = socket(AF_INET, SOCK_STREAM, 0);

            if(connect(sock, (struct sockaddr*)&adresse, adr_taille) < 0)
            {
                cout << endl << "Echec de la connexion au serveur" << endl << "Veuillez vérifier l'adresse ip du serveur et réessayer" << endl;
                connexion = -1;
            }
            else
            {
                connexion = 0;
            }
        }

        ThreadModifie* t = new ThreadModifie();
        t->lancerThread((void*)callBack, (void*)sock);


        char* bufTmp = new char[1024];
        strcpy(bufTmp, "jon|");
        char* test = (char*)pseudo.c_str();
        strcat(bufTmp, test);
        envoyerMessage(sock, bufTmp);


        while(enRoute == 0){

            const char* buf;

            cin >> buffer;

            buf = buffer.c_str();

            envoyerMessage(sock, buf);

        }
    }
    return 0;

}
