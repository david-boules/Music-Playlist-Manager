#ifndef USER_H
#define USER_H

#include <QDialog>

namespace Ui {
class User;
}

class User : public QDialog
{
    Q_OBJECT

public:
    explicit User(QWidget *parent = nullptr);
    ~User();

    static bool validateCredentials(const QString &username, const QString &password);

private:
    Ui::User *ui;
};

#endif // USER_H
