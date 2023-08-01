#include "tcpclient.h"

TcpClient::TcpClient(QObject *parent) : QObject(parent)
{
    connect(&_socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(&_socket, &QTcpSocket::errorOccurred, this, &TcpClient::onErrorOccurred);
}

TcpClient::~TcpClient(){
    delete file;
}

void TcpClient::connectToServer(const QString &ip, const QString &port)
{
    _socket.connectToHost(ip, port.toUInt());
}

void TcpClient::onConnected()
{
    qInfo() << "Подключение к серверу произошло успешно!";
    if (file->open(QIODevice::Append)) file->write("\n/////////////////////////////////////////////////////\n\nПодключение к серверу произошло успешно!\n");
    file->close();
}


void TcpClient::onErrorOccurred(QAbstractSocket::SocketError error)
{
    qWarning() << "Error: " << error;
    if (file->open(QIODevice::Append)) file->write(("\n/////////////////////////////////////////////////////\n\nError: Ошибка подключения к серверу\n"));
    file->close();
}
