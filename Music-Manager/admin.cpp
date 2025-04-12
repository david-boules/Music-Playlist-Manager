#include "admin.h"
#include "ui_admin.h"

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
