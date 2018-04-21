#include "client.h"

Client::Client()
{
    nom = (char*)malloc(256);
}

void Client::set_socket(int s)
{
    socket = s;
}

void Client::set_nom(char* n)
{
    strcmp(nom, n);
}

void Client::set_id(int i)
{
    id = i;
}

int Client::get_socket()
{
    return socket;
}

char* Client::get_nom()
{
    return nom;
}

int Client::get_id()
{
    return id;
}
