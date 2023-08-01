#ifndef SPECIALTHREAD_H
#define SPECIALTHREAD_H
#include <QThread>
#include "Bee.h"
#include "WinnieThePooh.h"
#include "Pyatochek.h"

class SpecialThread : public QThread
{
public:
    SpecialThread();
    ~SpecialThread();
    void setTestClass(Bee*);
    void setWinnieThePooh(WinnieThePooh*);
     void setPyatochek(Pyatochek*);
private:
    Bee* pTestObject;
    WinnieThePooh* pTestObjectW;
    Pyatochek* pTestObjectP;
public:
    void run();
};

#endif // SPECIALTHREAD_H
