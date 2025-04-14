#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "user.h"
#include "admin.h"
#include <QMessageBox>
#include <QVector>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PushButton_login_clicked()
{
    QString username = ui->LineEdit_username->text();
    QString password= ui->LineEdit_password->text();


    bool isAdmin = ui->radioButton_admin->isChecked();
    bool isUser = ui->radioButton_user->isChecked();

    if(isAdmin){
        if(Admin::validateLogin(username, password)){
            QMessageBox::information(this, "Login", "Admin Login Successful");
            hide();
            Admin *a = new Admin(this);
            a->show();
        }
        else{
            QMessageBox::warning(this, "Login", "Invalid admin username or password");
        }
    }

    else if(isUser){

        //loop over all user names and passwords

        if (User::validateCredentials(username, password)){
            QMessageBox::information(this, "Login", "User Login Successful");
            hide();
            User *u = new User(username, password, this);
            u->show();
            }

        else {
            QMessageBox::warning(this, "Login", "Invalid username or password");
        }
    }

    else{
        QMessageBox::warning(this, "Login", "Please select either 'User' or 'Admin'");
    }
}
