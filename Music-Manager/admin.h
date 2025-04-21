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

    static bool validateLogin(const QString &username, const QString &password);
    static void editAdminCredentials(const QString &new_username, const QString &new_password);
    void clearLineEdits();

private slots:
    void on_pushButton_listUsers_clicked();
    void on_pushButton_confirm_clicked();

    void on_CreateSong_clicked();

private:
    static QString admin_username;
    static QString admin_password;

    Ui::Admin *ui;
};

#endif // ADMIN_H
