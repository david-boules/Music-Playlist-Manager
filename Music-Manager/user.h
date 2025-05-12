#ifndef USER_H
#define USER_H

#include <QUrl>
#include <QMessageBox>
#include <QDialog>
#include <QString>
#include <QVector>
#include "songpage.h"
#include "playlistmanagement.h"
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
    explicit User(QString username, QString password,PlaylistManagement* playlist, QWidget *parent = nullptr);

    static bool validateCredentials(const QString &username, const QString &password);
    static bool usernameExists(const QString& username);

    static bool addUser(const QString& username, const QString& password, const QString& email, const QString& role);
    static bool deleteUser(const QString& username, const QString& password);
    static QString getUserRole(const QString& username);
    static QMap <QString, UserInfo> getAllUsers();

    static void loadUsers();
    static void saveUsers();
    static void loadLastPlayedSongs();
    static void saveLastPlayedSongs();
    static void loadLastPlaylist();
    static void saveLastPlaylist();

    static void setLastPlayed(const QString& username, const QString& song);
    static QString getLastPlayed(const QString& username);
    static void setLastPlaylist(const QString& username, const QString& playlist);
    static QString getLastPlaylist(const QString& username);

    QString get_username(){
        return UserName;
    }

    int getAllPlaylists();

    ~User();

private slots:

    void showEvent(QShowEvent *event) override; // to update elements of the user dashboard in case of going back to this page
    void on_viewPlaylists_clicked();
    void on_userReports_clicked();
    void on_searchSongs_clicked();
    void on_pushButton_back_clicked();

private:
    Ui::User *ui;
    QString UserName;
    QString Password;
    SongPage song_page;
    PlaylistManagement* playlist1;
    static QMap<QString, QString> LastPlayedMap;
    static QMap<QString, QString> LastPlaylistMap;


    static QMap<QString, UserInfo> UsersList;
};

#endif // USER_H
