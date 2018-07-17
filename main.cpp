#include <QCoreApplication>
#include "client.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Client dataSender;
    dataSender.work();
    return a.exec();
}
