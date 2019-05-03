#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDataStream>
#include <QFile>
#include <QTimer>

class MyTcpClient : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpClient(QObject *parent = nullptr);
    void connect(QHostAddress address = QHostAddress::LocalHost,
                     quint16 port = 1024);
    void sendMessage(QString msj);
    void sendData(QByteArray datagram);
    int getState();

signals:

public slots:

private:
    QTcpSocket *socket;

};

#endif // MYTCPCLIENT_H
