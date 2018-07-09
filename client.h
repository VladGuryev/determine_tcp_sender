#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QCoreApplication>
#include <QTcpSocket>
#include <QtNetwork>
#include <QHostAddress>
#include <iostream>
#include <QMessageBox>
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

private:
    QDataStream outputStream;

    quint16 PORT = 2540;
    QTcpSocket* m_pTcpSocket = nullptr;
};

#endif // SERVER_H
