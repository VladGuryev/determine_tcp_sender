#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    m_pTcpSocket = new QTcpSocket(this);

    connect(m_pTcpSocket, SIGNAL(hostFound()), SLOT(slotHostFound()));
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(clientConnected()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
               this, SLOT(slotError(QAbstractSocket::SocketError)));
    connect(m_pTcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
             this, SLOT(stateChanged(QAbstractSocket::SocketState)));
    for(int i = 0; i < 8; i++)
        this->packet.append('1');
    qDebug() <<"packet: " << packet;
}

void Client::work()
{
    m_pTcpSocket->connectToHost(QHostAddress::LocalHost, PORT);
    if (m_pTcpSocket->waitForConnected(1000))
         qDebug("Connected!");
}

void Client::clientConnected()
{
    cout << "client connected to server (VVOD_SLOT)"  << endl;
    int i = 0;
    while(i < 10000){
        m_pTcpSocket->write(packet);
        i++;
    }
}

void Client::slotHostFound()
{
    cout << "host was found" << endl;
}

void Client::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
            "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                         "The host was not found." :
                         err == QAbstractSocket::RemoteHostClosedError ?
                         "The remote host is closed." :
                         err == QAbstractSocket::ConnectionRefusedError ?
                         "The connection was refused." :
                         QString(m_pTcpSocket->errorString())
                        );
    cout << "slotError is: "<< err;
}

void Client::stateChanged(QAbstractSocket::SocketState state)
{
    QObject *socket = QObject::sender();
    QTcpSocket *sock = dynamic_cast<QTcpSocket*>(socket);
   // cout <<"socket type is: "<<sock->socketType() << endl;
    cout << "state of socket is: " << state << endl;
}

