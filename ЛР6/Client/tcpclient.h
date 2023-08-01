#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QFile>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr);
     ~TcpClient();
public slots:
    void connectToServer(const QString &ip, const QString &port);

private slots:
    void onConnected();
    void onErrorOccurred(QAbstractSocket::SocketError error);

public:
    QTcpSocket _socket;
    QFile* file;
};

#endif // TCPCLIENT_H
