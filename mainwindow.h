#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QHeaderView>
#include <QFileDialog>
#include <QPixmap>
#include <QBuffer>
#include <QDesktopServices>
#include <QUrl>
#include "mytcpserver.h"
#include "mytcpclient.h"
#include "myudpserver.h"
#include "myudpclient.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void getUdpData(QString msj);

    void getTcpData(QString msj);

    void on_actionAbout_triggered();

    void on_port_client_valueChanged(int arg1);

    void on_IP_address_editingFinished();

    void on_IP_radio_toggled(bool checked);

    void on_broadcast_radio_toggled(bool checked);

    void on_local_radio_toggled(bool checked);

    void on_message_radio_toggled(bool checked);

    void on_radio_file_toggled(bool checked);

    void on_protocol_client_currentIndexChanged(const QString &arg1);

    void on_send_button_clicked();

    void on_message_editingFinished();

    void on_file_path_editingFinished();

    void on_message_returnPressed();

    void on_protocol_server_currentIndexChanged(const QString &arg1);

    void on_port_server_valueChanged(int arg1);

    void on_IP_address_server_editingFinished();

    void on_IP_radio_server_toggled(bool checked);

    void on_Any_radio_server_toggled(bool checked);

    void on_connect_button_clicked();

    void on_disconnect_button_clicked();

    void on_open_button_clicked();

    void on_actionInstructions_triggered();

private:
    Ui::MainWindow *ui;
    QString _protocol_client, _protocol_server;
    quint16 _port_client, _port_server;
    QHostAddress _address_client, _address_server;
    QFile _file;
    QString _filename;
    QString _lastpath;
    QString _suffix;
    QString _msg;
    QString _type;
    MyUdpServer udp_server;
    MyUdpClient udp_client;
    MyTcpServer tcp_server;
    MyTcpClient tcp_client;
    QByteArray _datagram;
    QByteArray _udpdata, _tcpdata;
    QString _message, _path;
    int _row;

};

#endif // MAINWINDOW_H
