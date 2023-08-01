#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) : QObject(parent)
{
    connect(&_server, &QTcpServer::newConnection, this, &TcpServer::onNewConnection);
    if(_server.listen(QHostAddress::Any, 55555)) qDebug() << "Ожидание клиента...";
}

TcpServer::~TcpServer()
{
    delete mainWindow;
    delete file;
}

void TcpServer::onNewConnection()
{
    const auto client = _server.nextPendingConnection();
    if(client == nullptr) return;
    qDebug() << "Клиент подключился!";
    mainWindow->ui->listWidget->addItem("Клиент подключился!");
    if (file->open(QIODevice::Append)) file->write("Клиент подключился!\n");
    file->close();
    _clients.insert(this->getClientKey(client), client);
    connect(client, &QTcpSocket::readyRead, this, &TcpServer::onReadyRead);
    connect(client, &QTcpSocket::disconnected, this, &TcpServer::onClientDisconnected);
}

void TcpServer::onReadyRead()
{
    const auto client = qobject_cast<QTcpSocket*>(sender());
    if(!client) return;
    QString message = client->readAll();
    QString nstr = "", Hstr = "";
    int i = 0;
    bool flag = true;
    for(; message[i] != " "; nstr += message[i], ++i)
        if(message[i] < "0" || message[i] > "9") flag = false;
    for(++i; i - message.size(); Hstr += message[i], ++i)
        if(message[i] < "0" || message[i] > "9") flag = false;
    if(flag){
        n = nstr.toUInt();
        H = Hstr.toUInt();
        qDebug() << "Данные получены от клиента";
        qDebug() << "Количество пчёл: " + nstr;
        qDebug() << "Количество глотков горшке: " + Hstr;
        mainWindow->ui->listWidget->addItem("Данные получены от клиента");
        mainWindow->ui->listWidget->addItem("Количество пчёл: " + nstr);
        mainWindow->ui->listWidget->addItem("Количество глотков горшке: " + Hstr);
        if (file->open(QIODevice::Append)) {
        file->write("Данные получены от клиента\n");
        file->write(("Количество пчёл: " + nstr + "\n").toUtf8());
        file->write(("Количество глотков горшке: " + Hstr + "\n").toUtf8());
        file->close();
        }
        mainWindow->flag = true;
    }
    else {
        qDebug() << "Данные клиента введены некорректно";
        mainWindow->ui->listWidget->addItem("Данные клиента введены некорректно");
        if (file->open(QIODevice::Append)) file->write("Данные клиента введены некорректно\n");
        file->close();
    }
}

void TcpServer::onClientDisconnected()
{
    const auto client = qobject_cast<QTcpSocket*>(sender());
    if(!client) return;
    _clients.remove(this->getClientKey(client));
    qDebug() << "Клиент отключился";
    mainWindow->ui->listWidget->addItem("Клиент отключился");
    if (file->open(QIODevice::Append)) file->write("Клиент отключился\n");
    file->close();
}

QString TcpServer::getClientKey(const QTcpSocket *client) const
{
    return client->peerAddress().toString().append(":").append(QString::number(client->peerPort()));
}
