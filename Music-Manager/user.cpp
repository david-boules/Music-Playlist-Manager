#include "user.h"

User::User(QString name, QString pass, QString mail) : username(name), password(pass), email(mail) {}

QString User::getUsername()
{
    return username;
}
QString User::getPassword()
{
    return password;
}
QString User::getEmail()
{
    return email;
}

bool User::login(const QString& _username, const QString& _password) //checks if a user already exists in the users list
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].getUsername() == _username && users[i].getPassword() == _password)
        {
            return true;
        }
    }
    return false;
}
