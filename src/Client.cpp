#include "Client.h"

Client::Client()
{
    this->nom = (char*) malloc(256);
}

Client::~Client()
{
    //dtor
}

void Client::setNom(const char* n)
{
    snprintf(this->nom, 256, n);
}

void Client::setId(int i)
{
    this->id = i;
}
