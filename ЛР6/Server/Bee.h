#ifndef BEE_H
#define BEE_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

class Bee : public QObject
{
    Q_OBJECT
    private:
        bool *WinnieThePooh_sleep_got_enough_sleep;
        bool *Pyatochek_sleep_got_enough_sleep;
        bool *WinnieThePooh_sleep;
        MainWindow* mainWindow;
        bool *Pyatochek_sleep;
        int *barrel_fullness;
        QFile* file;
        QMutex* mutex;
        int index;
        int H;
    public:
        Bee(bool&, bool&, bool&, bool&, int&, int, int, MainWindow&, QMutex&, QFile&);
        ~Bee();
        Bee();
    public slots:
        void run();
    signals:
        void finished();

};

#endif // BEE_H
