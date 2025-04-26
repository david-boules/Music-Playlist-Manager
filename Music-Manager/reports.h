#ifndef REPORTS_H
#define REPORTS_H

#include <QDialog>

namespace Ui {
class Reports;
}

class Reports : public QDialog
{
    Q_OBJECT

public:
    explicit Reports(QWidget *parent = nullptr);
    ~Reports();

private slots:
    void on_pushButton_back_clicked();

private:
    Ui::Reports *ui;
};

#endif // REPORTS_H
