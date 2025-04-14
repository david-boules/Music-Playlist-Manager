#ifndef USER_H
#define USER_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class User;
}

class User : public QDialog
{
    Q_OBJECT

public:
    explicit User(QString username, QString password, QWidget *parent = nullptr);
    static bool validateCredentials(const QString &username, const QString &password);
    ~User();

private slots:
    void on_createPlaylist_clicked();

    void on_searchSongs_clicked();

    void on_viewPlaylist_clicked();

private:
    Ui::User *ui;
    QString UserName, Password;
    void loadUserData();
    QString getLastPlayedSong();
    int getAllPlaylists();
};

#endif // USER_H
