#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>

#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <iterator>
#include <unistd.h>
#include <cstring>

class Client
{
public:
    Client();

    void set_socket(int s);
    void set_nom(char* n);
    void set_id(int i);

    int get_socket();
    char* get_nom();
    int get_id();

private:
    int socket;
    char* nom;
    int id;
};

#endif // CLIENT_H
