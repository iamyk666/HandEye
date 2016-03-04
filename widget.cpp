#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    tcpSocket = new QTcpSocket(this);//创建一个tcpsocket连接
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(ethernetConnected()));

    //串口对象实例化
    mSerialPort = new QSerialPort;
    mSerialPortInfo = new QSerialPortInfo;
    //将信号与槽连接起来
    connect(mSerialPort,SIGNAL(readyRead()),this,SLOT(ReadMyCom()));
    connect(ui->textEditReceive,SIGNAL(textChanged()),this,SLOT(on_textBrowserRefesh()));

    QList<QSerialPortInfo> comInfoList = mSerialPortInfo->availablePorts();//获取可用串口列表
    if(comInfoList.isEmpty())//若没有可用串口，则发送警告
    {
        QMessageBox::warning(this,"Waring!","There's no avalible COM to use, plese check your serialport!");
    }
    else//将可用串口显示到comboBox上以供选择
    {
        for(int i = 0; i < comInfoList.size(); i ++)
        {
            ui->comboBoxRS232Port->addItem(comInfoList[i].portName());
        }
    }
    QStringList baudRateList = QStringList() << "1200" << "2400" << "4800"
                                             << "9600" << "14400" << "19200" << "38400" << "43000" << "57600"
                                             << "76800" << "115200" << "128000" << "230400" << "256000" <<"460800"
                                             << "921600" << "1382400";
    QStringList parityList = QStringList() << "无" << "奇校验" << "偶校验";
    QStringList stopBitsList = QStringList() << "1" << "1.5" << "2";
    QStringList dataBitsList = QStringList() << "8" << "7" << "6" << "5";

    ui->comboBoxRS232BaurdRate->addItems(baudRateList);

    ui->comboBoxRS232BaurdRate->setCurrentIndex(3);//设置9600为默认选项

    ui->comboBoxCheakBit->addItems(parityList);

    ui->comboBoxStopBit->addItems(stopBitsList);

    ui->comboBoxRS232Databit->addItems(dataBitsList);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::ReadMyCom()
{
    data_received = mSerialPort->readAll();//读取串口上所有数据
    QString str = QString::fromLocal8Bit(data_received);//将接受到的数据改变编码格式
    ui->textEditReceive->append("收到："+str);
}

void Widget::readMessage()
{
    //tcpsocket收到的数据
    while(tcpSocket->bytesAvailable()>0)
    {
        QByteArray datagram;
        datagram.resize(tcpSocket->bytesAvailable());
        tcpSocket->read(datagram.data(),datagram.size());
        QString message = QString::fromLocal8Bit(datagram.data());
        this->ui->textEditReceive->append("收到："+message);
    }
}

void Widget::connectStateChange()
{
    this->ui->labelEthernetIsConnected->setText("已连接");
}

void Widget::on_textBrowserRefesh()
{
    //设置每次接收到新数据时光标跟随移动
    ui->textEditReceive->moveCursor(QTextCursor::End);
}

void Widget::on_pushButtonRS232tConnect_clicked()
{
    try{
        mSerialPort->setPortName(this->ui->comboBoxRS232Port->currentText());
        mSerialPort->open(QIODevice::ReadWrite);//打开串口
        mSerialPort->setBaudRate(this->ui->comboBoxRS232BaurdRate->currentText().toInt());
        QString currentData = " ";//用于保存将要发送的数据
        currentData = ui->comboBoxRS232Databit->currentText();//读取textedit上的数据
        switch(currentData.toInt())
        {
            case 8:mSerialPort->setDataBits(QSerialPort::Data8);break;
            case 7:mSerialPort->setDataBits(QSerialPort::Data7);break;
            case 6:mSerialPort->setDataBits(QSerialPort::Data6);break;
            case 5:mSerialPort->setDataBits(QSerialPort::Data5);break;
        }
        mSerialPort->setFlowControl(QSerialPort::NoFlowControl);
        currentData = ui->comboBoxStopBit->currentText();
        int n = ui->comboBoxStopBit->currentIndex();
        switch(n)
        {
            case 0:mSerialPort->setStopBits(QSerialPort::OneStop);break;
            case 1:mSerialPort->setStopBits(QSerialPort::OneAndHalfStop);break;
            case 2:mSerialPort->setStopBits(QSerialPort::TwoStop);break;

        }
        int m = ui->comboBoxCheakBit->currentIndex();
        switch(m)
        {
            case 0:mSerialPort->setParity(QSerialPort::NoParity);break;
            case 1:mSerialPort->setParity(QSerialPort::EvenParity);break;
            case 2:mSerialPort->setParity(QSerialPort::OddParity);break;

        }
        if(mSerialPort->isOpen())
        {
            ui->pushButtonRS232tConnect->setDisabled(true);
            ui->labelRS232IsConnected->setText("已连接");
        }
        else
        {
            ui->labelRS232IsConnected->setText("未连接");
        }
    }
    catch(...)
    {
        QMessageBox::warning(this,"ERROR!","Cannot open the serialport!");
    }
}

void Widget::on_lineEditSend_returnPressed()
{
    QByteArray data;
    QString data1;
    data = this->ui->lineEditSend->text().toLocal8Bit();
    data1 = this->ui->lineEditSend->text();
    if(this->ui->radioButtonRS232->isChecked())
    {
        if(mSerialPort->isOpen())
            mSerialPort->write(data);
    }
    if(this->ui->radioButtonEthernet->isChecked())
    {
        if(tcpSocket->isOpen())
        {
            tcpSocket->write(data,data.size());
        }
    }
    this->ui->textEditReceive->append("发送："+data1);
    this->ui->lineEditSend->clear();
}

void Widget::on_radioButtonRS232_clicked()
{
    this->ui->pushButtonEthernetConnect->setEnabled(false);
    this->ui->pushButtonRS232tConnect->setEnabled(true);
}

void Widget::on_radioButtonEthernet_clicked()
{
    this->ui->pushButtonRS232tConnect->setEnabled(false);
    this->ui->pushButtonEthernetConnect->setEnabled(true);
}

void Widget::on_pushButtonEthernetConnect_clicked()
{
    QString ip = this->ui->lineEditRobotIP->text();
    QString port = this->ui->lineEditRobotPort->text();

    tcpSocket->connectToHost(ip,port.toInt());
    connect(tcpSocket,SIGNAL(hostFound()),this,SLOT(connectStateChange()));
}


//下面的槽没用。。。。。
void Widget::on_radioButtonRS232_pressed()
{
    //this->ui->pushButtonEthernetConnect->setCheckable(false);
}

void Widget::on_radioButtonEthernet_pressed()
{
    //this->ui->pushButtonRS232tConnect->setCheckable(false);
}


