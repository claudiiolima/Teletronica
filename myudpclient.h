#ifndef MYUDPCLIENT_H
#define MYUDPCLIENT_H

#include <QObject>
#include <QUdpSocket>

class MyUdpClient : public QObject
{
    Q_OBJECT
public:
    explicit MyUdpClient(QObject *parent = nullptr);
    void sendData(QByteArray datagram, QHostAddress address, quint16 port);

signals:

public slots:

private:
    QUdpSocket *socket;
};

#endif // MYUDPCLIENT_H
