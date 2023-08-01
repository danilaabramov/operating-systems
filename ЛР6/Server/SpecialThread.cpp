#include "SpecialThread.h"


SpecialThread::SpecialThread()
{
    pTestObject = 0;
    pTestObjectW = 0;
    pTestObjectP = 0;
}

SpecialThread::~SpecialThread()
{
    delete pTestObject;
    delete pTestObjectW;
    delete pTestObjectP;
}

void SpecialThread::setTestClass(Bee *pTO) {
    pTestObject = pTO;
}

void SpecialThread::setWinnieThePooh(WinnieThePooh *pTO) {
    pTestObjectW = pTO;
}

void SpecialThread::setPyatochek(Pyatochek *pTO) {
    pTestObjectP = pTO;
}

void SpecialThread::run() {
    if (pTestObject) {
         pTestObject->run();
    }
    if (pTestObjectW) {
         pTestObjectW->run();
    }
    if (pTestObjectP) {
         pTestObjectP->run();
    }
}
