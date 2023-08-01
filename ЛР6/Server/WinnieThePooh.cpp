#include "WinnieThePooh.h"

WinnieThePooh::WinnieThePooh(bool &ws, bool &wsges, int &fullness, int glotki, MainWindow &mw, QMutex& m, QFile& f)
{
    barrel_fullness = &fullness;
    H = glotki;
     mainWindow = &mw;
    WinnieThePooh_sleep = &ws;
    WinnieThePooh_sleep_got_enough_sleep = &wsges;
    file = &f;
    mutex = &m;
}

WinnieThePooh::~WinnieThePooh()
{
    delete barrel_fullness;
    delete  mainWindow;
    delete WinnieThePooh_sleep;
    delete WinnieThePooh_sleep_got_enough_sleep;
    delete mutex;
    delete file;
}

void WinnieThePooh::run() {
    while (1)
    {
        if(!*WinnieThePooh_sleep){
            Sleep(1000);
            qDebug()<<"Винни-Пуx всё съел";
            mainWindow->ui->listWidget->addItem("Винни-Пуx всё съел");
            if (file->open(QIODevice::Append)) {
                mutex->lock();
                file->write("Винни-Пуx всё съел\n");
                file->close();
                mutex->unlock();
            }
            *barrel_fullness = 0;
            *WinnieThePooh_sleep = true;
            *WinnieThePooh_sleep_got_enough_sleep = false;
        }
        if (!*WinnieThePooh_sleep_got_enough_sleep) {
            qDebug()<<"Винни-Пуx лёг спать";
            mainWindow->ui->listWidget->addItem("Винни-Пуx лёг спать");
            if (file->open(QIODevice::Append)) {
                mutex->lock();
                file->write("Винни-Пуx лёг спать\n");
                file->close();
                mutex->unlock();
            }
            Sleep(6000);
            qDebug()<<"Винни-Пуx выспался";
            mainWindow->ui->listWidget->addItem("Винни-Пуx выспался");
            if (file->open(QIODevice::Append)) {
                mutex->lock();
                file->write("Винни-Пуx выспался\n");
                file->close();
                mutex->unlock();
            }
            *WinnieThePooh_sleep_got_enough_sleep = true;
        }
        Sleep(1000);
    }
    emit finished();
}
