#include "SpecialThread.h"
#include "tcpserver.h"
#include <QFile>
int main(int argc, char *argv[])
{
    QApplication qApplication2(argc, argv);
    MainWindow mainWindow2;
    QFile file("log.txt");
    if (file.open(QIODevice::Append)) file.write("\n/////////////////////////////////////////////////////\n\nОжидание клиента...\n");
    file.close();
    TcpServer server;
    server.mainWindow = &mainWindow2;
    server.file = &file;
    mainWindow2.setWindowIcon(QIcon(":/resources/img/icon.png"));
    mainWindow2.ui->label->setPixmap(QPixmap(":resources/img/Pyatochek.png"));
    mainWindow2.ui->label_2->setPixmap(QPixmap(":resources/img/WinnieThePooh.png"));
    mainWindow2.setWindowTitle("Задача о Винни-Пухе и Пятачке");
    mainWindow2.setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    mainWindow2.file = &file;
    mainWindow2.show();
    mainWindow2.ui->listWidget->addItem("Ожидание клиента...");
    QMutex mutex;
QMutex mutex2;
    qApplication2.exec();
    if(server.mainWindow->flag)
    {
        QApplication qApplication(argc, argv);
        MainWindow mainWindow;
        mainWindow.flag = true;
        mainWindow.ui->pushButton->setText("Стоп");
        mainWindow.ui->label->setPixmap(QPixmap(":resources/img/Pyatochek.png"));
        mainWindow.ui->label_2->setPixmap(QPixmap(":resources/img/WinnieThePooh.png"));
        mainWindow.setWindowIcon(QIcon(":/resources/img/icon.png"));
        mainWindow.setWindowTitle("Задача о Винни-Пухе и Пятачке");
        mainWindow.setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
        mainWindow.show();
        srand(time(0));
        bool WinnieThePooh_sleep = true, WinnieThePooh_sleep_got_enough_sleep = false;
        bool Pyatochek_sleep = true, Pyatochek_sleep_got_enough_sleep = false;
        int barrel_fullness = 0;
        const int n = server.n, H = server.H;
        SpecialThread* bee = new SpecialThread[n];
        SpecialThread winniethePooh;
        SpecialThread pyatochek;
        Bee** thread1 = new Bee*[n];
        for(int i = 0; i - n; ++i) thread1[i] = new Bee(WinnieThePooh_sleep, Pyatochek_sleep, WinnieThePooh_sleep_got_enough_sleep,
                                                     Pyatochek_sleep_got_enough_sleep, barrel_fullness, H, i + 1, mainWindow, mutex2, file);
        WinnieThePooh thread2(WinnieThePooh_sleep, WinnieThePooh_sleep_got_enough_sleep, barrel_fullness, H, mainWindow, mutex, file);
        Pyatochek thread3(Pyatochek_sleep, Pyatochek_sleep_got_enough_sleep, barrel_fullness, H, mainWindow, mutex, file);
        for(int i = 0; i - n; ++i) bee[i].setTestClass(thread1[i]);
        winniethePooh.setWinnieThePooh(&thread2);
        pyatochek.setPyatochek(&thread3);
        for(int i = 0; i - n; ++i) bee[i].start();
        winniethePooh.start();
        pyatochek.start();


        qApplication.exec();
        delete[] bee;
        for(int i = 0; i - n;  delete thread1[i++]);
        file.close();
    }
}

