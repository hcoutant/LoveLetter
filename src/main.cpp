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
            cout << buffer;
        }
    }
}

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
    }
    else if(choix == "2")
    {
        int sock;
        int connexion = -1;
        string ip;
        string buffer;

        socklen_t adr_taille = sizeof(struct sockaddr_in);

        struct sockaddr_in adresse;
        adresse.sin_family = AF_INET;
        adresse.sin_port = htons(12345);

        while(connexion != 0)
        {
            cout << endl << "ip du serveur: " << endl;
            cin >> ip;

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

        while(enRoute == 0){

            const char* buf;

            cin >> buffer;

            buf = buffer.c_str();

            send(sock, buf, strlen(buf), 0);

        }
    }
    return 0;

}
