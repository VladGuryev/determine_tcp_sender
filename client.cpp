#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    m_pTcpSocket = new QTcpSocket(this);

    connect(m_pTcpSocket, SIGNAL(hostFound()), SLOT(slotHostFound()));
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(clientConnected()));


}

void Client::work()
{
     m_pTcpSocket->connectToHost(QHostAddress::LocalHost, PORT);
}

void Client::clientConnected()
{
    cout << "client connected to server (VVOD_SLOT)";
}

void Client::slotHostFound()
{
    cout << "host was found";
}

