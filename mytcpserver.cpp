#include "mytcpserver.h"

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
}

void MyTcpServer::startServer(QHostAddress address, quint16 port)
{
    if (!server) { server = new QTcpServer(this); }
    connect(server,SIGNAL(newConnection()),this,SLOT(openConnection()));
    if (!server->listen(address,port)) { return; }
    socket = new QTcpSocket;
}

void MyTcpServer::finishServer()
{
    if (socket) {
        socket->close();
        socket->disconnectFromHost();
    }
}

QByteArray MyTcpServer::getData()
{
    return datagram;
}

void MyTcpServer::openConnection()
{

    socket = server->nextPendingConnection();
    socket->waitForReadyRead(1);
    datagram.clear();
    QByteArray temp;
    while(true){
        temp = socket->read(1024);
        socket->waitForReadyRead(5);
        if(temp.isEmpty()) break;
        datagram.append(temp);
    }
//    datagram = socket->readAll();
    qDebug() << datagram.size();
    qDebug() << ":bytes" << socket->bytesAvailable();
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
