#include "admin.h"
#include "ui_admin.h"
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

QString Admin::admin_username = "admin";
QString Admin::admin_password = "admin123";

bool Admin::validateLogin(const QString &username, const QString &password) {
    return username == admin_username && password == admin_password;
}

void Admin::editAdminCredentials(const QString &new_username, const QString &new_password){
    admin_username = new_username;
    admin_password = new_password;
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

    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    QString email = ui->lineEdit_email->text();

    if (username.isEmpty() || password.isEmpty() || email.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields are required.");
        return;
    }

    if (password.length() < 8) {
        QMessageBox::warning(this, "Password Error", "Password must be at least 8 characters.");
        return;
    }

    QString path = QDir::currentPath() + "/users.txt";
    qDebug() << "[DEBUG] Using users.txt path:" << QFileInfo(path).absoluteFilePath();

    if (add_user) {
        QFile readFile(path);
        if (readFile.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream in(&readFile);
            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList fields = line.split(",");
                if (fields.size() >= 1 && fields[0] == username) {
                    QMessageBox::warning(this, "Duplicate User", "Username already exists!");
                    readFile.close();
                    return;
                }
            }
            readFile.close();
        }

        QFile writeFile(path);
        if (!writeFile.open(QFile::WriteOnly | QFile::Text | QFile::Append)) {
            QMessageBox::warning(this, "Warning", "Could not open file for writing.");
            return;
        }

        QTextStream out(&writeFile);
        out << username << "," << password << "," << email << "\n";
        writeFile.flush();
        writeFile.close();

        QMessageBox::information(this, "Success", "User added successfully!");
        clearLineEdits();
    }

    else if (delete_user) {
        QFile file(path);
        QFile tempFile(QDir::currentPath() + "/users_temp.txt");

        if (!file.open(QFile::ReadOnly | QFile::Text) || !tempFile.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Could not open file.");
            return;
        }

        QTextStream ifile(&file);
        QTextStream ofile(&tempFile);
        bool found = false;

        while (!ifile.atEnd()) {
            QString line = ifile.readLine();
            QStringList fields = line.split(",");
            if (fields.size() >= 1 && fields[0] == username) {
                found = true;
                continue;
            }
            ofile << line << "\n";
        }

        file.close();
        tempFile.close();

        file.remove();
        tempFile.rename(path);

        if (found) {
            QMessageBox::information(this, "Success", "User deleted successfully");
        } else {
            QMessageBox::warning(this, "Not Found", "Username not found");
        }

        clearLineEdits();
    }

    else {
        QMessageBox::warning(this, "Warning", "Please select either add or delete.");
    }
}

void Admin::on_pushButton_listUsers_clicked()
{
    QString path = QDir::currentPath() + "/users.txt";
    QFile file(path);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Could not open file.");
        return;
    }

    QTextStream users(&file);
    ui->listWidget_users->clear();

    while (!users.atEnd()) {
        QString line = users.readLine();
        QStringList fields = line.split(",");
        if (fields.size() >= 3) {
            QString display = "Username: " + fields[0] + " | Password: " + fields[1] + " | Email: " + fields[2];
            ui->listWidget_users->addItem(display);
        }
    }

    file.close();
}
