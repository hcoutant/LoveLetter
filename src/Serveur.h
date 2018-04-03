#ifndef SERVEUR_H
#define SERVEUR_H

#include <iostream>
#include <vector>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>

#include "ThreadModifie.h"
#include "Client.h"
#include "jeu.h"

using namespace std;

class Serveur
{
    public:
        Serveur();
        virtual ~Serveur();

        void accepterClient();
        static void* callBack(void* args);
        static void decomposerMessage(string m);
        static void envoyerATous(char* m);
        static void envoyerA(int i, char* m);

        void lancerPartie();

        static int nbJoueurMax;
        static int nbJoueurCo;

        static char* action;
        static int ready;
        static int indexJoueurActuel;
    protected:

    private:

        static vector<Client> clients;

        static vector<char*> instructions;

        int socketServeur, socketClient;
        struct sockaddr_in adresseServeur, adresseClient;
        char buff[256];

        static int trouverIndexClient(Client* c);
};

#endif // SERVEUR_H
