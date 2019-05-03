#ifndef MYUDPSERVER_H
#define MYUDPSERVER_H

#include <QObject>
#include <QWidget>
#include <QMessageBox>
#include <QUdpSocket>
#include <QDesktopServices>
#include <QUrl>
#include <QFile>
#include <QFileDialog>

class MyUdpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyUdpServer(QObject *parent = nullptr);
    void startServer(QHostAddress address = QHostAddress::Any,
                     quint16 port = 1024);
    void finishServer();
    void received();
    int getState();
    QByteArray getData();

signals:
    void toUI(QString);

public slots:
    void receiveData();

private:
    QObject *parent;
    QUdpSocket *socket;
    QByteArray datagram;
    int _state;
};

#endif // MYUDPSERVER_H
