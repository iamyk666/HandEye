#include "imageacqdialog.h"
#include "ui_imageacqdialog.h"

ImageAcqDialog::ImageAcqDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageAcqDialog)
{
    ui->setupUi(this);
}

ImageAcqDialog::~ImageAcqDialog()
{
    delete ui;
}

void ImageAcqDialog::on_pushButtonOpenCamera_clicked()
{
    qDebug()<<"打开相机槽调用。。。"<<endl;
}

void ImageAcqDialog::on_pushButtonGrab_clicked()
{
    qDebug()<<"抓取槽调用..."<<endl;
}
