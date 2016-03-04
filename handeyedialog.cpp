#include "handeyedialog.h"
#include "ui_handeyedialog.h"

HandEyeDialog::HandEyeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HandEyeDialog)
{
    ui->setupUi(this);
}

HandEyeDialog::~HandEyeDialog()
{
    delete ui;
}

void HandEyeDialog::on_pushButtonOpenImageFile_clicked()
{
    //这里的fileNames拿到之后可以读入这些图像
    QStringList fileNames = QFileDialog::getOpenFileNames(
                this,"open file","/","jpeg files(*.jpeg)::png files(*.png)::jpg files(*.jpg)");
    for(int i = 0;i<fileNames.size();i++)
    {
        qDebug()<<fileNames.at(i).toStdString().c_str()<<endl;
    }
}
