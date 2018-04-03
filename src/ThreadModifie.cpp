#include "ThreadModifie.h"

ThreadModifie::ThreadModifie()
{
    //ctor
}

ThreadModifie::~ThreadModifie()
{
    //dtor
}


int ThreadModifie::lancerThread(void* callBack, void* args)
{
    int tret = 0;

    tret = pthread_create(&this->tid, NULL, (void *(*)(void*))callBack, args);

    if(tret)
    {
        cerr << "Erreur dans la creation du thread";
        return tret;
    }
    else
    {
        return 0;
    }
}
