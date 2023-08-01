#include "mainwindow.h"
#include "tcpclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    TcpClient client;
    QFile file("log.txt");
    client.file = &file;
    w.file = &file;
    w._socket = &client._socket;
    client.connectToServer("127.1.2.3", "55555");
    w.setWindowTitle("Задача о Винни-Пухе и Пятачке");
    w.setWindowIcon(QIcon(":/resources/img/icon.png"));
    w.setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    w.show();
    return a.exec();
}
