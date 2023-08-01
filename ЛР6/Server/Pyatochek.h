#ifndef PYATOCHEK_H
#define PYATOCHEK_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

class Pyatochek : public QObject
{
    Q_OBJECT
    public:
        Pyatochek(bool&, bool&, int&, int, MainWindow&, QMutex&, QFile&);
        ~Pyatochek();
    private:
        int *barrel_fullness;
        int H;
        QMutex* mutex;
        QFile* file;
        MainWindow*  mainWindow;
        QTextStream* textStream;
        bool *Pyatochek_sleep;
        bool *Pyatochek_sleep_got_enough_sleep;
    public slots:
        void run();
    signals:
        void finished();
};

#endif // PYATOCHEK_H
