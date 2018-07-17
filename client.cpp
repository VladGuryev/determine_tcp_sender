#include "client.h"
//https://stackoverflow.com/questions/20546750/qtcpsocket-reading-and-writing
//https://ru.stackoverflow.com/questions/654257/qtimer-%d0%bd%d0%b5-%d1%81%d1%80%d0%b0%d0%b1%d0%b0%d1%82%d1%8b%d0%b2%d0%b0%d0%b5%d1%82

Client::Client(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    timer = new QTimer(this);
    timer->setInterval(2000);

    connect(timer, SIGNAL(timeout()), this, SLOT(writeData()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(slotError(QAbstractSocket::SocketError)));
 //   connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
    //        this, SLOT(stateChanged(QAbstractSocket::SocketState)));

}

void Client::work()
{
    socket->connectToHost(QHostAddress::LocalHost, PORT);
    if (socket->waitForConnected(1000)){
         cout << "Client connected to the VVOD_SLOT" << endl;
         timer->start();
    } else {
        cout << "Client did not connect to the VVOD_SLOT" << endl;
        return;
    }
}

Client::~Client()
{
    delete this->socket;
    delete this->timer;
}

void Client::writeData()
{
    static bool in = false;
    QByteArray data1 = "1:31FE1CEB15B9120F";
    QByteArray data2 = "2:F4740C7150157340";
    QByteArray data3 = "1:654A3C23FABC123B";
    QByteArray data4 = "2:CF180A926BCA7399";

    if(socket->state() == QAbstractSocket::ConnectedState){
        if(in == false){
            socket->write(data1);
            socket->waitForBytesWritten(1000);
            socket->write(data2);
            socket->waitForBytesWritten(1000);
            in = true;
        } else {
            socket->write(data3);
            socket->waitForBytesWritten(1000);
            socket->write(data4);
            socket->waitForBytesWritten(1000);
            in = false;
        }
    }
}

void Client::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
            "Log: " + (err == QAbstractSocket::HostNotFoundError ?
                         "The host was not found." :
                         err == QAbstractSocket::RemoteHostClosedError ?
                         "The remote host is closed." :
                         err == QAbstractSocket::ConnectionRefusedError ?
                         "The connection was refused." :
                         QString(socket->errorString())
                        );
    cerr <<  strError.toStdString() << endl;
}

void Client::stateChanged(QAbstractSocket::SocketState state)
{
    QObject *socket = QObject::sender();
    QTcpSocket *sock = dynamic_cast<QTcpSocket*>(socket);
    cout <<"socket type is: "<<sock->socketType() << endl;
    cout << "state of socket is: " << state << endl;
}

