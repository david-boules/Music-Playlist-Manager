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

    //usernames and passwords are hardcoded for now
    QVector<QString> usernames = {"Alex", "Bob", "Charlie"};
    QVector<QString> passwords = {"Alex1234", "Bob123abc", "Charlie1"};
    QString admin_username = "admin";
    QString admin_password = "admin123";


    bool isAdmin = ui->radioButton_admin->isChecked();

    if(isAdmin){
        if(username == admin_username && password == admin_password){
            QMessageBox::information(this, "Login", "Admin Login Successful");
            hide();
            Admin *a = new Admin(this);
            a->show();
        }
        else{
            QMessageBox::warning(this, "Login", "Invalid admin username or password");
        }
    }

    else{

        //loop over all user names and passwords

        bool user_found = false;
        for(qsizetype i=0; i < usernames.size(); i++){ //'qsizetype' is Qt's platform-safe type meant for container indexing (e.g., QVector indexing)
            if(usernames[i] == username && passwords[i] == password){
                user_found = true;
                break;
            }
        }
        if(user_found){
            QMessageBox::information(this, "Login", "User Login Successful");
            hide();
            User *u = new User(this);
            u->show();
        }
        else{
            QMessageBox::warning(this, "Login", "Invalid username or password");
        }
    }
}
