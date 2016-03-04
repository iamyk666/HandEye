#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork>
#include <QString>

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QByteArray>

#include <QDebug>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    QByteArray data_received;//用于缓存从串口读取的数据
    QByteArray data_send;//用于保存即将发送的数据

    QTextCodec *tc = QTextCodec::codecForName("UTF-8");//编码格式

private slots:
    void ReadMyCom();//定义槽函数

    void readMessage();

    void connectStateChange();

    void on_textBrowserRefesh();

    void on_pushButtonRS232tConnect_clicked();

    void on_lineEditSend_returnPressed();

    void on_radioButtonRS232_clicked();

    void on_radioButtonEthernet_clicked();

    void on_radioButtonRS232_pressed();

    void on_radioButtonEthernet_pressed();

    void on_pushButtonEthernetConnect_clicked();

private:
    Ui::Widget *ui;

    QTcpSocket *tcpSocket;//客户端socket

    QSerialPort *mSerialPort;//声明serial对象
    QSerialPortInfo *mSerialPortInfo;//声明serialinfo对象
};

#endif // WIDGET_H
