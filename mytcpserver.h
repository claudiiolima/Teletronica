#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QFileInfo>
#include <QFileDialog>
#include <QDataStream>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDesktopServices>
#include <QUrl>
#include <QImage>
#include <QBuffer>

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
    void startServer(QHostAddress address = QHostAddress::Any,
                     quint16 port = 1024);
    void finishServer();
    QByteArray getData();

signals:
    void toUI(QString msj);

public slots:
    void openConnection();

private:
    QTcpServer *server;
    QTcpSocket *socket;
    QByteArray datagram;
    quint32 blockSize;
    QString filename;
};

#endif // MYTCPSERVER_H
