#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>

namespace Ui {
class Admin;
}

class Admin : public QDialog
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();

    QString newAccountRole();
    void clearLineEdits();

private slots:
    void on_pushButton_listUsers_clicked();
    void on_pushButton_confirm_clicked();
    void on_CreateSong_clicked();
    void on_pushButton_back_clicked();

private:
    Ui::Admin *ui;
};

#endif // ADMIN_H
