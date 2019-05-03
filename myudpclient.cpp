#include "myudpclient.h"

MyUdpClient::MyUdpClient(QObject *parent) : QObject(parent)
{
    socket = new QUdpSocket(this);
}

void MyUdpClient::sendData(QByteArray datagram, QHostAddress address, quint16 port)
{
    socket->writeDatagram(datagram.data(),address,port);
}
