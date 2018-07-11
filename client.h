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
#include <QTimer>
using namespace std;

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    void work();
    ~Client();
signals:

public slots:
    void writeData();

private:
    quint16 PORT = 2540;
    QTcpSocket* socket = nullptr;
    QTimer *timer;
private:
    QByteArray IntToArray(qint32 source); //Use qint32 to ensure that the number have 4 bytes

private slots:
    void slotHostFound();
    void slotError(QAbstractSocket::SocketError err);
    void stateChanged(QAbstractSocket::SocketState);
};

#endif // SERVER_H
