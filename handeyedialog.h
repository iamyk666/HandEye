#ifndef HANDEYEDIALOG_H
#define HANDEYEDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QString>
#include <QStringList>
#include <QDebug>

namespace Ui {
class HandEyeDialog;
}

class HandEyeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HandEyeDialog(QWidget *parent = 0);
    ~HandEyeDialog();

private slots:
    void on_pushButtonOpenImageFile_clicked();

private:
    Ui::HandEyeDialog *ui;
};

#endif // HANDEYEDIALOG_H
