#ifndef USER_H
#define USER_H
#include <QString>
#include <vector>

class User
{
private:
    QString username, password, email;
    std::vector<User> users;


public:
    User(QString name, QString pass, QString mail);

    QString getUsername();
    QString getPassword();
    QString getEmail();
    bool login(const QString& _username, const QString& _password);


};


#endif // USER_H
