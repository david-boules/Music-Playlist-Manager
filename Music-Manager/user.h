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

    void loadUserData();
    QString getLastPlayedSong();
    QString getAllPlaylists();

    ~User();

private slots:
    void on_createPlaylist_clicked();

    void on_searchSongs_clicked();

    void on_viewPlaylist_clicked();

private:
    Ui::User *ui;
    QString UserName;
    QString Password;
};

#endif // USER_H
