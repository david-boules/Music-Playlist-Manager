#include "user.h"
#include "ui_user.h"

User::User(QString username, QString password, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::User)
{
    ui->setupUi(this);
    ui->label_welcome->setText("Welcome " + username);
    ui->label_lastPlayedSong->setText("Last Played Song: " + getLastPlayedSong());
    ui->label_summary->setText("Total Playlists: " + QString::number(getAllPlaylists()));
}
User::~User()
{
    delete ui;
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

void User::on_createPlaylist_clicked() {
    QMessageBox::about(this, "Playlist", "Create Playlist");
}

void User::on_searchSongs_clicked() {
    QMessageBox::about(this, "Search", "Search Songs");
}

void User::on_viewPlaylist_clicked() {
    QMessageBox::about(this, "Playlist", "View Playlists");
}

QString User::getLastPlayedSong() {
    return "";
}
