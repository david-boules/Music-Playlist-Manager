#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "user.h"
#include "admin.h"
#include <QMessageBox>
#include <QVector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->LineEdit_username->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PushButton_login_clicked()
{
    QString username = ui->LineEdit_username->text();
    QString password= ui->LineEdit_password->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login", "Please enter both username and password.");
        return;
    }

    if (!User::validateCredentials(username, password)) {
        QMessageBox::warning(this, "Login", "Invalid username or password.");
        return;
    }

    QString role = User::getUserRole(username).toLower();

    if (role == "admin") {
        QMessageBox::information(this, "Login", "Admin Login Successful");
        hide();
        Admin *a = new Admin(this);
        a->show();
    }
    else {
        QMessageBox::information(this, "Login", "User Login Successful");
        hide();
        User *u = new User(username, password, this);
        u->show();
    }
}
