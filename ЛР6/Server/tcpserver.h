#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include "mainwindow.h"
#include "ui_mainwindow.h"

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);
    ~TcpServer();
public slots:
    void onNewConnection();
    void onReadyRead();
    void onClientDisconnected();
private:
    QString getClientKey(const QTcpSocket *client) const;
public:
    QTcpServer _server;
    MainWindow* mainWindow;
    QFile* file;
    QHash<QString, QTcpSocket*> _clients;
    int n;
    int H;
};

#endif // TCPSERVER_H
