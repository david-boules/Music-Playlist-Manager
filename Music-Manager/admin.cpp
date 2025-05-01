// admin username: admin | admin password: admin123

#include "admin.h"
#include "ui_admin.h"
#include "user.h"
#include "songpage.h"
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QFileInfo>

Admin::Admin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Admin)
{
    ui->setupUi(this);
}

void Admin::clearLineEdits() {
    ui->lineEdit_username->clear();
    ui->lineEdit_password->clear();
    ui->lineEdit_email->clear();
}

Admin::~Admin()
{
    delete ui;
}

void Admin::on_pushButton_confirm_clicked(){

    bool add_user = ui->radioButton_addUser->isChecked();
    bool delete_user = ui->radioButton_deleteUser->isChecked();

    if(!ui->radioButton_user->isChecked() && !ui->radioButton_admin->isChecked()) {
        QMessageBox::warning(this, "Warning", "Please select either Admin or User.");
        return;
    }

    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    QString email = ui->lineEdit_email->text();
    QString role = newAccountRole();

    if (username.isEmpty() || password.isEmpty() || email.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields are required.");
        return;
    }

    if (password.length() < 8) {
        QMessageBox::warning(this, "Password Error", "Password must be at least 8 characters.");
        return;
    }

    if (add_user) {
        if (User::usernameExists(username)) {
            QMessageBox::warning(this, "Duplicate User", "Username already exists!");
        } else {
            User::addUser(username, password, email, role);
            QMessageBox::information(this, "Success", "User added successfully!");
            clearLineEdits();
        }
    }

    else if (delete_user) {
        if (!User::deleteUser(username, password)) { // If valid, username and corresponding password are deleted in this 'if condition'
            QMessageBox::warning(this, "Not Found", "Incorrect Username or Password.");
        } else {
            QMessageBox::information(this, "Success", "User deleted successfully!");
            clearLineEdits();
        }
    }

    else {
        QMessageBox::warning(this, "Warning", "Please select either Add or Delete.");
    }
}

void Admin::on_pushButton_listUsers_clicked() {
    ui->listWidget_users->clear();

    auto users = User::getAllUsers();
    for (auto it = users.begin(); it != users.end(); it++) {
        QString display = "Username: " + it.key() + " | Password: " + it.value().password + " | Email: " + it.value().email + " | Role: " + it.value().role;
        ui->listWidget_users->addItem(display);
        }
    }

void Admin::on_CreateSong_clicked()
{
    hide();
    SongPage *songpage= new SongPage(this);
    songpage->show();
}


void Admin::on_pushButton_back_clicked()
{
    this->close();
    if (parentWidget()) { //returns a pointer to the widget that opened the current window (checking to make sure a parent exists)
        parentWidget()->show(); //therefore can be used to go back
    }
}

QString Admin::newAccountRole()
{
    if(ui->radioButton_user->isChecked()) {
        return "user";
    }
    else {
        return "admin";
    }
}

