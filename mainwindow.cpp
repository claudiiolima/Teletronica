#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow),
    _protocol_client("TCP"), _protocol_server("TCP"),
    _port_client(1024), _port_server(1024),
    _address_client(QHostAddress("127.0.0.1")),
    _address_server(QHostAddress("127.0.0.1")),
    _type("MESSAGE"),
    _row(0)
{
    ui->setupUi(this);
    QPixmap pixmap(":/logo.png");
    ui->logo->setPixmap(pixmap);
    ui->logo->setScaledContents(true);
    ui->logo->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
//    ui->logo->setMask(pixmap.mask());
//    ui->logo->show();

    connect(&udp_server,SIGNAL(toUI(QString)),this,SLOT(getUdpData(QString)));

    connect(&tcp_server,SIGNAL(toUI(QString)),this,SLOT(getTcpData(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getUdpData(QString msj)
{
    if (msj.length() > 31) {
        for (int i = 0; i < msj.length(); i+=31) {
            ui->message_list->addItem(msj.mid(i,31));
            ui->message_list->item(_row)->setTextAlignment(Qt::AlignLeft);
            ui->message_list->item(_row)->setBackgroundColor("#42A5F5"); // ///////////////////// ESCOLHER COR DE FUNDO
            _row++;
        }
    } else {
        ui->message_list->addItem(msj);
        ui->message_list->item(_row)->setTextAlignment(Qt::AlignLeft);
        ui->message_list->item(_row)->setBackgroundColor("#42A5F5"); // ///////////////////// ESCOLHER COR DE FUNDO
        _row++;
    }
}

void MainWindow::getTcpData(QString msj)
{
    if (msj.length() > 31) {
        for (int i = 0; i < msj.length(); i+=31) {
            ui->message_list->addItem(msj.mid(i,31));
            ui->message_list->item(_row)->setTextAlignment(Qt::AlignLeft);
            ui->message_list->item(_row)->setBackgroundColor("#42A5F5"); // ///////////////////// ESCOLHER COR DE FUNDO
            _row++;
        }
    } else {
        ui->message_list->addItem(msj);
        ui->message_list->item(_row)->setTextAlignment(Qt::AlignLeft);
        ui->message_list->item(_row)->setBackgroundColor("#42A5F5"); // ///////////////////// ESCOLHER COR DE FUNDO
        _row++;
    }
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this,tr("Sobre"),tr("MIT LICENSE\n"
                                                 "Copyright (c) 2019 Claudio Lima\n\n"
                                                 "Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the \"Software\"), to deal "
                                                 "in the Software without restriction, including without limitation the rights "
                                                 "to use, copy, modify, merge, publish, distribute, sublicense, and/or sell "
                                                 "copies of the Software, and to permit persons to whom the Software is "
                                                 "furnished to do so, subject to the following conditions:\n\n"

                                                 "The above copyright notice and this permission notice shall be included in all "
                                                 "copies or substantial portions of the Software.\n\n"

                                                 "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR "
                                                 "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, "
                                                 "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE "
                                                 "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER "
                                                 "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, "
                                                 "OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE "
                                                 "SOFTWARE."));
    // MIT LICENSE
}

void MainWindow::on_actionInstructions_triggered()
{
    QMessageBox::information(this,tr("Instruções"),tr("O programa funciona na forma de chat."
                                                      "Para conversar é necessário conhecer o endereço ip do "
                                                      "destinatário, assim como o inverso."
                                                      "Algumas limitações: tamanho máximo via TCP 2586539 bytes"
                                                      "                                       UDP  próximode de 100000 bytes"));
}


// ////////////////////////////////////////////////////////////////////////////////////// //
//                                      CLIENT METODES                                    //
void MainWindow::on_port_client_valueChanged(int arg1)
{
    _port_client = quint16(arg1);
}

void MainWindow::on_IP_address_editingFinished()
{
    _address_client = QHostAddress(ui->IP_address->text());
}

void MainWindow::on_IP_radio_toggled(bool checked)
{
    ui->IP_address->setText("");
    ui->IP_address->setEnabled(checked);
    if (checked)
        _address_client = QHostAddress(ui->IP_address->text());
}

void MainWindow::on_broadcast_radio_toggled(bool checked)
{
    ui->IP_address->setDisabled(checked);
    if (checked) {
        _address_client = QHostAddress::Broadcast;
        ui->IP_address->setText(_address_client.toString());
    }
}

void MainWindow::on_local_radio_toggled(bool checked)
{
    ui->IP_address->setDisabled(checked);
    if (checked) {
        _address_client = QHostAddress::LocalHost;
        ui->IP_address->setText(_address_client.toString());
    }
}

void MainWindow::on_message_radio_toggled(bool checked)
{
    ui->message->setEnabled(checked);
    ui->open_button->setDisabled(checked);
    ui->file_path->setDisabled(checked);
    if (checked) _type = "MESSAGE";
}

void MainWindow::on_radio_file_toggled(bool checked)
{
    ui->open_button->setEnabled(checked);
    ui->file_path->setEnabled(checked);
    ui->message->setDisabled(checked);
    if (checked) _type = "FILE";
}

void MainWindow::on_open_button_clicked()
{
    _filename = "";
    _lastpath = "";
    ui->file_path->setText(_filename);
    _filename = QFileDialog::getOpenFileName(this,tr("Abrir arquivo"),tr("/home/"));
    if(_filename == tr("")) { QMessageBox::warning(this, tr("AVISO"), tr("Arquivo não foi selecionado."));
    } else {
        QFileInfo s(_filename);
        _suffix = s.suffix();
        _lastpath = s.fileName();
        ui->file_path->setText(_filename);
    }
}

void MainWindow::on_protocol_client_currentIndexChanged(const QString &arg1)
{
    _protocol_client = arg1;
}

void MainWindow::on_message_editingFinished()
{
    _message = ui->message->text();
}

void MainWindow::on_file_path_editingFinished()
{
    _path = ui->file_path->text();
}

void MainWindow::on_send_button_clicked()
{
    for (int i = 0; i < 200000000; i++) {
        ui->progressBar->setTextVisible(true);
        ui->progressBar->setValue(i/2000000);
    }
    if (!_protocol_client.compare("TCP")) {
        if (!_type.compare("MESSAGE")) {
            _datagram.clear();
            _datagram.append("MES");
            _datagram.append(_message);
            tcp_client.connect(_address_client,_port_client);
            tcp_client.sendData(_datagram);
            if (_message.length() > 31) {
                for (int i = 0; i < _message.length(); i+=31) {
                    ui->message_list->addItem(_message.mid(i,31));
                    ui->message_list->item(_row)->setTextAlignment(Qt::AlignRight);
                    ui->message_list->item(_row)->setBackgroundColor("#DFFDC1");
                    _row++;
                }
            } else {
                ui->message_list->addItem(_message);
                ui->message_list->item(_row)->setTextAlignment(Qt::AlignRight);
                ui->message_list->item(_row)->setBackgroundColor("#DFFDC1");
                _row++;
            }
            _message = "";
            ui->message->setText(_message);
            _message = "";
            ui->message->setText(_message);
        } else if (!_type.compare("FILE")) {
            _datagram.clear();
            _file.setFileName(_filename);
            if (!_file.open(QFile::ReadOnly))
                return;

            _datagram.append("FIL");
            _datagram.append(QString::number(_suffix.size()).toUtf8());
            _datagram.append(_suffix.toUtf8());
            _datagram.append(_file.readAll());
            _file.close();
            tcp_client.connect(_address_client,_port_client);
            tcp_client.sendData(_datagram);
            if (_file.fileName().length() > 31) {
                for (int i = 0; i < _file.fileName().length(); i+=31) {
                    ui->message_list->addItem(_file.fileName().mid(i,31));
                    ui->message_list->item(_row)->setTextAlignment(Qt::AlignRight);
                    ui->message_list->item(_row)->setBackgroundColor("#DFFDC1");
                    _row++;
                }
            } else {
                ui->message_list->addItem(_file.fileName());
                ui->message_list->item(_row)->setTextAlignment(Qt::AlignRight);
                ui->message_list->item(_row)->setBackgroundColor("#DFFDC1");
                _row++;
            }

        }
        ui->progressBar->setValue(0);
    } else if (!_protocol_client.compare("UDP")) {
        if (!_type.compare("MESSAGE")) {
            _datagram.clear();
            _datagram.append("MES");
            _datagram.append(_message);
            udp_client.sendData(_datagram,_address_client,_port_client);
            if (_message.length() > 31) {
                for (int i = 0; i < _message.length(); i+=31) {
                    ui->message_list->addItem(_message.mid(i,31));
                    ui->message_list->item(_row)->setTextAlignment(Qt::AlignRight);
                    ui->message_list->item(_row)->setBackgroundColor("#DFFDC1");
                    _row++;
                }
            } else {
                ui->message_list->addItem(_message);
                ui->message_list->item(_row)->setTextAlignment(Qt::AlignRight);
                ui->message_list->item(_row)->setBackgroundColor("#DFFDC1");
                _row++;
            }
            _message = "";
            ui->message->setText(_message);
        } else if (!_type.compare("FILE")) {
            _datagram.clear();
            _file.setFileName(_filename);
            if (!_file.open(QFile::ReadOnly))
                return;

            _datagram.append("FIL");
            _datagram.append(QString::number(_suffix.size()).toUtf8());
            _datagram.append(_suffix.toUtf8());
            _datagram.append(_file.readAll());
            _file.close();
            udp_client.sendData(_datagram,_address_client,_port_client);
            if (_file.fileName().length() > 31) {
                for (int i = 0; i < _file.fileName().length(); i+=31) {
                    ui->message_list->addItem(_file.fileName().mid(i,31));
                    ui->message_list->item(_row)->setTextAlignment(Qt::AlignRight);
                    ui->message_list->item(_row)->setBackgroundColor("#DFFDC1");
                    _row++;
                }
            } else {
                ui->message_list->addItem(_file.fileName());
                ui->message_list->item(_row)->setTextAlignment(Qt::AlignRight);
                ui->message_list->item(_row)->setBackgroundColor("#DFFDC1");
                _row++;
            }
        }
        ui->progressBar->setValue(0);
    }
}

void MainWindow::on_message_returnPressed()
{
    on_message_editingFinished();
    on_send_button_clicked();
}

//                                                                                        //
// ////////////////////////////////////////////////////////////////////////////////////// //


// ////////////////////////////////////////////////////////////////////////////////////// //
//                                      SERVER METODES                                    //
void MainWindow::on_port_server_valueChanged(int arg1)
{
    _port_server = quint16(arg1);
}

void MainWindow::on_IP_address_server_editingFinished()
{
    _address_server = QHostAddress(ui->IP_address_server->text());
}

void MainWindow::on_IP_radio_server_toggled(bool checked)
{
    ui->IP_address_server->setText("");
    ui->IP_address_server->setEnabled(checked);
    if (checked)
        _address_server = QHostAddress(ui->IP_address_server->text());
}

void MainWindow::on_Any_radio_server_toggled(bool checked)
{
    ui->IP_address_server->setDisabled(checked);
    if (checked) {
        _address_server = QHostAddress::Broadcast;
        ui->IP_address_server->setText(_address_server.toString());
    }
}

void MainWindow::on_protocol_server_currentIndexChanged(const QString &arg1)
{
    if (!_protocol_server.compare("TCP")) {
        ui->connect_button->setText("Vincular");
        ui->disconnect_button->setText("Desvincular");

    } else if (!_protocol_server.compare("UDP")) {
        ui->connect_button->setText("Conectar");
        ui->disconnect_button->setText("Desconectar^");
        udp_server.finishServer();
    }
    _protocol_server = arg1;
}

void MainWindow::on_connect_button_clicked()
{
    if (!_protocol_server.compare("TCP")) {
        tcp_server.startServer(QHostAddress::Any,_port_server);
//        tcp_server.openConnection();
        ui->connect_label->setText("Conectado");
    } else if (!_protocol_server.compare("UDP")) {
        if(udp_server.getState() != 0) {
            QMessageBox::warning(this,tr("Aviso"),tr("É necessário desvincular a porta ao endereço antes de vincular novamente."));
        } else {
            udp_server.startServer(_address_server,_port_server);
            if(udp_server.getState() == 4) {
                QMessageBox::information(this,tr("Aviso"),tr("Porta foi vinculado ao endereço com sucesso."));
                ui->connect_label->setText("Vinculado");
            }
        }
    }
}

void MainWindow::on_disconnect_button_clicked()
{
    if (!_protocol_server.compare("TCP")) {
        tcp_server.finishServer();
        ui->connect_label->setText("Desconectado");
    } else if (!_protocol_server.compare("UDP")) {
        udp_server.finishServer();
        ui->connect_label->setText("Desvinculado");
    }
}
