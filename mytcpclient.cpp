#include "mytcpclient.h"

MyTcpClient::MyTcpClient(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
}

void MyTcpClient::connect(QHostAddress address, quint16 port)
{
    socket->connectToHost(address,port);
    socket->waitForConnected();
}

void MyTcpClient::sendData(QByteArray datagram)
{
    socket->flush();
    qDebug() << "escrito:" << socket->write(datagram);
    socket->waitForBytesWritten();
    socket->flush();
    socket->close();
}

int MyTcpClient::getState()
{
    return socket->state();
}
