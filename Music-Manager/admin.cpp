#include "admin.h"
#include "ui_admin.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

Admin::Admin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Admin)
{
    ui->setupUi(this);
}

QString Admin::admin_username = "admin";
QString Admin::admin_password = "admin123";

bool Admin:: validateLogin(const QString &username, const QString &password) {
    return username == admin_username && password == admin_password;
}

void Admin::editAdminCredentials(const QString &new_username, const QString &new_password){
    admin_username = new_username;
    admin_password = new_password;
}

Admin::~Admin()
{
    delete ui;
}

void Admin::on_pushButton_confirm_clicked()
//'delete user' functionality still not working
{
    QString username=ui->lineEdit_username->text();
    QString password=ui->lineEdit_password->text();
    QString email=ui->lineEdit_email->text();


    if (username.isEmpty() || password.isEmpty() || email.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields are required.");
        return;
    }

    if (password.length() < 8) {
        QMessageBox::warning(this, "Password Error", "Password must be at least 8 characters.");
        return;
    }

    QFile file("users.txt");
    if(!file.open(QFile::WriteOnly | QFile::Text | QFile::Append)){
        QMessageBox::warning(this,"Warning","File not open");
    }
    QTextStream out(&file);
    out << username << "," << password << "," << email << "\n";
    file.flush();
    file.close();
    QMessageBox::information(this, "Success", "User added successfully!");

    ui->lineEdit_username->clear();
    ui->lineEdit_password->clear();
    ui->lineEdit_email->clear();


}

void Admin::on_pushButton_listUsers_clicked()
{
    QFile file("users.txt");
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","File not open");
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    file.close();

    ui->textEdit_userList->setPlainText(text);

}
