#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "imageacqdialog.h"
#include "handeyedialog.h"
#include "widget.h"

#include "QDebug"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ImageAcqDialog *dialog;
    HandEyeDialog *handeye;
    Widget *commWidget;
public slots:
    void onOpenCameraGrabberClicked();
private slots:
    void on_pushButtonOpenCameraGrabber_clicked();
    void on_pushButtonHandEyeCalib_clicked();
    void setComm();
};

#endif // MAINWINDOW_H
