#ifndef SERVEUR_H
#define SERVEUR_H

#include <iostream>
#include <vector>
#include <thread>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>

#include "client.h"
#include "joueur.h"
#include "jeu.h"

using namespace std;

class Serveur
{
public:
    Serveur(int n);
    virtual ~Serveur();

    void lancer_serveur();
    void eteindre_serveur();

    static void ecoute_client(Client *);

    static void decomposer_message(char* m);

    static void envoyer_a(int i, char* m);
    static void envoyer_tous(char* m);

    bool get_client_par_id(int i);

protected:

private:
    static int nb_max;
    static int index_joueur_actuel;

    static std::vector<Client*> liste_clients;
    static std::vector<char*> instructions;
    static std::vector<Joueur*> liste_joueurs;

    static Jeu* jeu;

    static int socket_serveur;
    int socket_client;

    struct sockaddr_in adresse_serveur;
    struct sockaddr_in adresse_client;

    static void ajouter_main(int i);

    static bool en_jeu;
};

#endif // SERVEUR_H
