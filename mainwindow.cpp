#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QObject::connect(this->ui->pushButtonOpenCameraGrabber,SIGNAL(clicked),this,SLOT(onOpenCameraGrabberClicked()));
    connect(this->ui->pushButtonSetCommParam,SIGNAL(clicked()),this,SLOT(setComm()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOpenCameraGrabberClicked()
{

    qDebug()<<"button pressed..."<<endl;
}

void MainWindow::on_pushButtonOpenCameraGrabber_clicked()
{
    qDebug()<<"clicked..."<<endl;
    dialog = new ImageAcqDialog();

    //dialog->show();
    dialog->exec();
}

void MainWindow::on_pushButtonHandEyeCalib_clicked()
{
    qDebug()<<"Hand eye calib..."<<endl;
    handeye = new HandEyeDialog();
    handeye->setWhatsThis("这个是手眼关系标定的对话框。");
    handeye->setWindowTitle("手眼标定");
    handeye->exec();
}

void MainWindow::setComm()
{
    commWidget = new Widget();
    commWidget->setWindowTitle("通信参数设置");
    commWidget->show();
}
