#include "reports.h"
#include "ui_reports.h"

Reports::Reports(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Reports)
{
    ui->setupUi(this);
}

Reports::~Reports()
{
    delete ui;
}

void Reports::on_pushButton_back_clicked()
{
    this->close();
    if (parentWidget()) { //returns a pointer to the widget that opened the current window (checking to make sure a parent exists)
        parentWidget()->show(); //therefore can be used to go back
    }
}
