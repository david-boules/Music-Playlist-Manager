#ifndef USER_H
#define USER_H

#include <QMessageBox>
#include <QDialog>
#include <QString>
#include <QVector>

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

    static void loadUsers();
    static void saveUsers();

    QString getLastPlayedSong();
    QString getAllPlaylists();

    ~User();

private slots:

    void on_searchSongs_clicked();

    void on_viewPlaylists_clicked();

    void on_pushButton_back_clicked();

    void on_userReports_clicked();

private:
    Ui::User *ui;
    QString UserName;
    QString Password;
    static QMap<QString, QString> usernames_and_passwords;
};

#endif // USER_H
