#ifndef QMAINDIALOG_H
#define QMAINDIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_newSimulation_pushButton_clicked();
    void on_animationStep_toolButton_clicked();

private:
    Ui::Dialog *ui;
};

#endif // QMAINDIALOG_H
