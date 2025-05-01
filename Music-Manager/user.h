#ifndef USER_H
#define USER_H

#include <QMessageBox>
#include <QDialog>
#include <QString>
#include <QVector>

// Struct containning the password, email, and role of each user to be used in the 'UsersList' map data structure
struct UserInfo {
    QString password;
    QString email;
    QString role;
};

namespace Ui {
class User;
}

class User : public QDialog
{
    Q_OBJECT

public:
    explicit User(QString username, QString password, QWidget *parent = nullptr);

    static bool validateCredentials(const QString &username, const QString &password);
    static bool usernameExists(const QString& username);

    static bool addUser(const QString& username, const QString& password, const QString& email, const QString& role);
    static bool deleteUser(const QString& username, const QString& password);
    static QString getUserRole(const QString& username);
    static QMap <QString, UserInfo> getAllUsers();

    static void loadUsers();
    static void saveUsers();


    QString getLastPlayedSong();
    int getAllPlaylists();

    ~User();

private slots:

    void on_viewPlaylists_clicked();
    void on_userReports_clicked();
    void on_searchSongs_clicked();
    void on_pushButton_back_clicked();

private:
    Ui::User *ui;
    QString UserName; // temporary
    QString Password; // temporary

    static QMap<QString, UserInfo> UsersList; // 'UsersList' - Data structure to store and handle users (for milestone 2)
};

#endif // USER_H
