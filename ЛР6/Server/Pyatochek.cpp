#include "Pyatochek.h"

Pyatochek::Pyatochek(bool &ps, bool &psges, int &fullness, int glotki, MainWindow &mw, QMutex& m, QFile& f)
{
    barrel_fullness = &fullness;
    H = glotki;
    mainWindow = &mw;
    Pyatochek_sleep = &ps;
    Pyatochek_sleep_got_enough_sleep = &psges;
    file = &f;
    mutex = &m;
}

Pyatochek::~Pyatochek()
{
    delete barrel_fullness;
    delete mainWindow;
    delete Pyatochek_sleep;
    delete Pyatochek_sleep_got_enough_sleep;
    delete mutex;
    delete file;
}

void Pyatochek::run() {
    while (1)
    {
        if(!*Pyatochek_sleep)
        {
            Sleep(1000);
            qDebug() <<"Пятачёк съел 1/4 горшка";
            mainWindow->ui->listWidget->addItem("Пятачёк съел 1/4 горшка");
            if (file->open(QIODevice::Append)) {
                mutex->lock();
                file->write("Пятачёк съел 1/4 горшка\n");
                file->close();
                mutex->unlock();
            }
            *barrel_fullness = *barrel_fullness * 0.75;
            *Pyatochek_sleep = true;
            *Pyatochek_sleep_got_enough_sleep = false;
        }
        if (!*Pyatochek_sleep_got_enough_sleep)
        {
            qDebug() <<"Пятачёк лёг спать";
            mainWindow->ui->listWidget->addItem("Пятачёк лёг спать");
            if (file->open(QIODevice::Append)) {
                mutex->lock();
                file->write("Пятачёк лёг спать\n");
                file->close();
                mutex->unlock();
            }
            Sleep(3000);
            qDebug() <<"Пятачёк выспался";
            mainWindow->ui->listWidget->addItem("Пятачёк выспался");
            if (file->open(QIODevice::Append)) {
                mutex->lock();
                file->write("Пятачёк выспался\n");
                file->close();
                mutex->unlock();
            }
            *Pyatochek_sleep_got_enough_sleep = true;
        }
        Sleep(1000);
    }
    emit finished();
}
