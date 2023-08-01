#ifndef WINNIETHEPOOH_H
#define WINNIETHEPOOH_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

class WinnieThePooh : public QObject
{
    Q_OBJECT
    public:
        WinnieThePooh(bool&, bool&, int&, int, MainWindow&, QMutex&, QFile&);
        ~WinnieThePooh();
    private:
        int *barrel_fullness;
        int H;
        QMutex* mutex;
        MainWindow*  mainWindow;
        QFile* file;
        QTextStream* textStream;
        bool *WinnieThePooh_sleep;
        bool *WinnieThePooh_sleep_got_enough_sleep;

    public slots:
        void run();
    signals:
        void finished();
};

#endif // WINNIETHEPOOH_H
