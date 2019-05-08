#include "myudpserver.h"

MyUdpServer::MyUdpServer(QObject *parent) : QObject(parent), parent(parent), _state(0)
{
    socket = new QUdpSocket(this);
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
    QByteArray tmp;
    datagram.clear();
    while(socket->hasPendingDatagrams()) {
        tmp.resize(int(socket->pendingDatagramSize()));

        QHostAddress sender;
        quint16 senderPort;

        socket->readDatagram(tmp.data(),tmp.size(),&sender,&senderPort);
        datagram.append(tmp);
    }
    QString type = datagram.mid(0,3);
    datagram.remove(0,3);
    if (!type.compare("FIL")) {
        int i = QString(datagram.mid(0,1)).toInt();
        datagram.remove(0,1);
        QString suffix = datagram.mid(0,i);
        datagram.remove(0,i);
        QString filename = QFileDialog::getSaveFileName(nullptr,tr("Salvar arquivo"));
        if (!filename.endsWith("."+suffix)) {
            filename = filename + "." + suffix;
        }
        QFileInfo f(filename);
        emit toUI(f.fileName());

        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly))
            return;

        file.write(datagram);
        file.close();

        QDesktopServices::openUrl(QUrl(filename));

    } else if (!type.compare("MES")) {
        emit toUI(QString(datagram));
    }
}
