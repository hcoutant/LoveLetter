#ifndef CALLBACK_H
#define CALLBACK_H

#include <QObject>

class CallBack: public QObject
{
    Q_OBJECT
public:
    CallBack();
    ~CallBack();

    virtual void call(char* a);
};

#endif // CALLBACK_H
