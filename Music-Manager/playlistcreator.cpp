#include "playlist.h"
#include "playlistcreator.h"
#include "playlistmanagement.h"
#include "songpage.h"
#include "ui_playlistcreator.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

PlaylistCreator::PlaylistCreator(const QString& username, QWidget *parent)
    : QDialog(parent), ui(new Ui::PlaylistCreator), user(username)
{
    ui->setupUi(this);
    loadSongs();
}

PlaylistCreator::~PlaylistCreator()
{
    delete ui;
}

void PlaylistCreator::loadSongs() {
    // Should read the user's vector stored in the map NOT songs.txt:
    ui->tableWidget_songs->setColumnCount(4);
    ui->tableWidget_songs->setHorizontalHeaderLabels({"Title", "Artist", "Album", "Duration"});
    ui->tableWidget_songs->setRowCount(0);

    const QVector<Song>& songs = SongPage::getSongLibrary();

    for(const Song& song : songs) {
        int row = ui->tableWidget_songs->rowCount();
        ui->tableWidget_songs->insertRow(row);
        ui->tableWidget_songs->setItem(row, 0, new QTableWidgetItem(song.getTitle()));
        ui->tableWidget_songs->setItem(row, 1, new QTableWidgetItem(song.getArtist()));
        ui->tableWidget_songs->setItem(row, 2, new QTableWidgetItem(song.getAlbum()));
        ui->tableWidget_songs->setItem(row, 3, new QTableWidgetItem(song.getDuration()));
    }
}



void PlaylistCreator::on_pushButton_back_clicked()
{
    this->close();
    if (parentWidget()) { //returns a pointer to the widget that opened the current window (checking to make sure a parent exists)
        parentWidget()->show(); //therefore can be used to go back
    }
}


void PlaylistCreator::on_createPlaylist_clicked()
{
    QString playlistName = ui->lineEdit_playlistName->text().trimmed();
    if(playlistName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Playlist name cannot be empty.");
        return;
    }

    const QVector<Playlist>& existingPlaylists = PlaylistManagement::getUserPlaylist(user);
    for (const Playlist& playlist: existingPlaylists) {
        if (playlist.getName() == playlistName) {
            QMessageBox::warning(this, "Duplicate Name", "A playlist with the name\"" + playlistName + "\" already exists.");
            return;
        }
    }

    QList<QTableWidgetSelectionRange> ranges = ui->tableWidget_songs->selectedRanges();
    if(ranges.isEmpty()) {
        QMessageBox::warning(this, "Error", "Select at least one song.");
        return;
    }



    Playlist newPlaylist(playlistName);
    for (const auto& range: ranges) {
        for(int row = range.topRow(); row <= range.bottomRow(); row++) {
            QString title = ui->tableWidget_songs->item(row, 0)->text();
            QString artist = ui->tableWidget_songs->item(row, 1)->text();
            QString album = ui->tableWidget_songs->item(row, 2)->text();
            QString duration = ui->tableWidget_songs->item(row, 3)->text();
            newPlaylist.addSong(Song(title, artist, album, duration));
        }
    }

    PlaylistManagement::addUserPlaylist(user, newPlaylist);
    QMessageBox::information(this, "Success", "Playlist saved");
}

