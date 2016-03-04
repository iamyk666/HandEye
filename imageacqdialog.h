#ifndef IMAGEACQDIALOG_H
#define IMAGEACQDIALOG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class ImageAcqDialog;
}

class ImageAcqDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImageAcqDialog(QWidget *parent = 0);
    ~ImageAcqDialog();

private slots:
    void on_pushButtonOpenCamera_clicked();

    void on_pushButtonGrab_clicked();

private:
    Ui::ImageAcqDialog *ui;
};

#endif // IMAGEACQDIALOG_H
