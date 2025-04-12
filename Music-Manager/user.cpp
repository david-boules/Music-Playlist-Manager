#include "user.h"
#include "ui_user.h"

User::User(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::User)
{
    ui->setupUi(this);
}

bool User::validateCredentials(const QString &username, const QString &password) {

    //usernames & passwords are hardcoded for now:
    QVector<QString> usernames = {"Alex", "Bob", "Charlie"};
    QVector<QString> passwords = {"Alex1234", "Bob123abc", "Charlie1"};
    for (qsizetype i = 0; i < usernames.size(); ++i) {
        if (usernames[i] == username && passwords[i] == password) {
            return true;
        }
    }
    return false;
}

User::~User()
{
    delete ui;
}
