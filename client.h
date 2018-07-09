#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QCoreApplication>
#include <QTcpSocket>
#include <QtNetwork>
#include <QHostAddress>
#include <iostream>
#include <QMessageBox>
#include <QDebug>
#include <QByteArray>
using namespace std;

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    void work();

signals:

public slots:
    void clientConnected();
    void slotHostFound();
    void slotError(QAbstractSocket::SocketError err);
    void stateChanged(QAbstractSocket::SocketState);
private:
    QDataStream outputStream;

    quint16 PORT = 2540;
    QTcpSocket* m_pTcpSocket = nullptr;
    QByteArray packet;
};

#endif // SERVER_H
