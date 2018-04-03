#ifndef THREADMODIFIE_H
#define THREADMODIFIE_H

#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>

#include <cstdlib>

using namespace std;

class ThreadModifie
{
    public:
        ThreadModifie();
        virtual ~ThreadModifie();

        pthread_t tid;

        int lancerThread(void* callBack, void* args);
    protected:

    private:
};

#endif // THREADMODIFIE_H
