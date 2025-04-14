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
