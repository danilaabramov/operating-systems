#include "Bee.h"

Bee::Bee(){}
Bee::Bee(bool &ws, bool &ps, bool &wsges, bool &psges, int &fullness, int h, int i, MainWindow &mw, QMutex& m, QFile& f)
{
    WinnieThePooh_sleep_got_enough_sleep = &wsges;
    Pyatochek_sleep_got_enough_sleep = &psges;
    barrel_fullness = &fullness;
    WinnieThePooh_sleep = &ws;
    Pyatochek_sleep = &ps;
    mainWindow = &mw;
    mutex = &m;
    index = i;
    H = h;
    file = &f;
}

Bee::~Bee()
{
    delete WinnieThePooh_sleep_got_enough_sleep;
    delete Pyatochek_sleep_got_enough_sleep;
    delete WinnieThePooh_sleep;
    delete Pyatochek_sleep;
    delete barrel_fullness;
    delete mainWindow;
    delete mutex;
    delete file;
}

void Bee::run() {
    while (1)
    {
        Sleep(1000);
        mutex->lock();
        if(*barrel_fullness < H)
        {
            ++*barrel_fullness;
            qDebug() << "Пчела " + QString::number(index) + " принесла каплю";
            mainWindow->ui->listWidget->addItem("Пчела " + QString::number(index) + " принесла каплю");
            if (file->open(QIODevice::Append)) {file->write("Пчела " + QByteArray::number(index) + " принесла каплю\n");file->close();}
            if (*barrel_fullness == H)
            {
                while (!*WinnieThePooh_sleep_got_enough_sleep && !*Pyatochek_sleep_got_enough_sleep) Sleep(1000);
                if (*WinnieThePooh_sleep_got_enough_sleep && *Pyatochek_sleep_got_enough_sleep)
                    if (rand() & 1)
                    {

                        qDebug() << "Пчела " + QString::number(index) + " разбудила Пятачка";
                        mainWindow->ui->listWidget->addItem("Пчела " + QString::number(index) + " разбудила Пятачка");
                        if (file->open(QIODevice::Append)){ file->write("Пчела " + QByteArray::number(index) + " разбудила Пятачка\n");file->close();}
                        *Pyatochek_sleep = false;
                        *Pyatochek_sleep_got_enough_sleep = false;
                    }
                    else
                    {

                        qDebug() << "Пчела " + QString::number(index) + " разбудила Винни-Пуxа";
                        mainWindow->ui->listWidget->addItem("Пчела " + QString::number(index) + " разбудила Винни-Пуxа");
                        if (file->open(QIODevice::Append)) {file->write("Пчела " + QByteArray::number(index) + " разбудила Винни-Пуxа\n");file->close();}
                        *WinnieThePooh_sleep = false;
                        *WinnieThePooh_sleep_got_enough_sleep = false;
                    }
                else if (*WinnieThePooh_sleep_got_enough_sleep)
                {

                    qDebug() << "Пчела " + QString::number(index) + " разбудила Винни-Пуxа";
                    mainWindow->ui->listWidget->addItem("Пчела " + QString::number(index) + " разбудила Винни-Пуxа");
                    if (file->open(QIODevice::Append)) {file->write("Пчела " + QByteArray::number(index) + " разбудила Винни-Пуxа\n");file->close();}
                    *WinnieThePooh_sleep = false;
                    *WinnieThePooh_sleep_got_enough_sleep = false;
                }
                else
                {

                    qDebug() << "Пчела " + QString::number(index) + " разбудила Пятачка";
                    mainWindow->ui->listWidget->addItem("Пчела " + QString::number(index) + " разбудила Пятачка");
                    if (file->open(QIODevice::Append)) {file->write("Пчела " + QByteArray::number(index) + " разбудила Пятачка\n");file->close();}
                    *Pyatochek_sleep = false;
                    *Pyatochek_sleep_got_enough_sleep = false;
                }
            }
        }
        mutex->unlock();
    }
    emit finished();
}
