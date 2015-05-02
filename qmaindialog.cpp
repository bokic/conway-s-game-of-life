#include "qmaindialog.h"
#include "ui_qmaindialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    ui->widget->newImage();
}

void Dialog::on_toolButton_2_clicked()
{
    ui->widget->step();
}
