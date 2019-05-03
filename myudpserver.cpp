#include "myudpserver.h"

MyUdpServer::MyUdpServer(QObject *parent) : QObject(parent), parent(parent), _state(0)
{
    socket = new QUdpSocket(this);
//    connect(socket,SIGNAL(readyRead()),this,SLOT(receiveData()));
//    socket->bind(ip,port);
}

void MyUdpServer::startServer(QHostAddress address, quint16 port)
{
    if (!socket) { socket = new QUdpSocket(this); }
    if (!socket->state()) {
        connect(socket,SIGNAL(readyRead()),this,SLOT(receiveData()));
        socket->bind(address,port);
        _state = socket->state();
    }
}

void MyUdpServer::finishServer()
{
    if(socket) {
        socket->disconnectFromHost();
        _state = socket->state();
    }
}

void MyUdpServer::received()
{
    if(socket->hasPendingDatagrams()) {
        qDebug() << datagram;
    }
}

int MyUdpServer::getState()
{
    return _state;
}

QByteArray MyUdpServer::getData()
{
    return datagram;
}

void MyUdpServer::receiveData()
{
    while(socket->hasPendingDatagrams()) {
        datagram.resize(int(socket->pendingDatagramSize()));

        QHostAddress sender;
        quint16 senderPort;

        socket->readDatagram(datagram.data(),datagram.size(),&sender,&senderPort);
//        QFile file(QFileDialog::getSaveFileName(nullptr,tr("Abrir arquivo")));
//        if (!file.fileName().isEmpty()) {
//               // Write contents of ba in file
//               file.write(datagram.data());
//               // Close the file
//               file.close();
//            }
//        QDesktopServices::openUrl(QUrl(file.fileName()));

        qDebug() << "Message from: " << sender.toString();
        qDebug() << "Message port: " << senderPort;
        qDebug() << "Message: " << datagram;

        emit toUI(datagram);
    }
}
