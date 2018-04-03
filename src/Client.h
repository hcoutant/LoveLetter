#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>

#include <cstdio>
#include <cstdlib>

class Client
{
    public:
        Client();
        virtual ~Client();

        void setNom(const char* n);
        void setId(int i);

        char* nom;
        int id;

        int socket;

    protected:

    private:
};

#endif // CLIENT_H
