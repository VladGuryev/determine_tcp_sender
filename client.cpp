#include "client.h"
//https://stackoverflow.com/questions/20546750/qtcpsocket-reading-and-writing

Client::Client(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    timer = new QTimer(this);
   // connect(timer, SIGNAL(timeout()), this, SLOT(writeData()));
    connect(socket, SIGNAL(connected()), SLOT(writeData()));

    /*  connect(socket, SIGNAL(hostFound()), SLOT(slotHostFound()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(slotError(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(stateChanged(QAbstractSocket::SocketState)));
    */
}

void Client::work()
{
    socket->connectToHost(QHostAddress::LocalHost, PORT);
    if (socket->waitForConnected(1000)){
         qDebug("Connected to the VVOD_SLOT");
      //   timer->start(1000);
    } else {
        cout << "client did not connect to the VVOD_SLOT";
    }
}

Client::~Client()
{
    delete this->socket;
    delete this->timer;
}

void Client::writeData()
{
    QByteArray data;
    //data = "1";
    data.resize(8);
    data[0] = '1';
    data[1] = '1';
    data[2] = '1';
    data[3] = '1';
    data[4] = '1';
    data[5] = '1';
    data[6] = '1';
    data[7] = '1';
    while(true){
        if(socket->state() == QAbstractSocket::ConnectedState){
        //  socket->write(IntToArray(data.size())); //write size of data
            socket->write(data);
            cout << socket->waitForBytesWritten(3000);
        }
    }
}

QByteArray Client::IntToArray(qint32 source)
{
    //Avoid use of cast, this is the Qt way to serialize objects
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);

    //data.setVersion(QDataStream::Qt_5_6);
    //data.device()->seek(0);
    //data << quint16(temp.size() - sizeof(quint16));

    data << source;
    return temp;
}

void Client::slotHostFound()
{
   // cout << "host was found" << endl;
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
                         QString(socket->errorString())
                        );
    cout << "slotError is: "<< err;
}

void Client::stateChanged(QAbstractSocket::SocketState state)
{
    QObject *socket = QObject::sender();
    QTcpSocket *sock = dynamic_cast<QTcpSocket*>(socket);
    cout <<"socket type is: "<<sock->socketType() << endl;
    cout << "state of socket is: " << state << endl;
}

