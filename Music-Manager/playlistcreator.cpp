#include "playlistcreator.h"
#include "ui_playlistcreator.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

PlaylistCreator::PlaylistCreator(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PlaylistCreator)
{
    ui->setupUi(this);
}

PlaylistCreator::~PlaylistCreator()
{
    delete ui;
}

void PlaylistCreator::loadSongs() {
    QFile file("songs.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");
        if (parts.size() == 4) {
            Song song = {parts[0], parts[1], parts[2], parts[3]};
            songLibrary.append(song);
            ui->listWidget_songs->addItem(song.getTitle() + " - " + song.getArtist());
        }
    }
    file.close();
}

void PlaylistCreator::on_createPlaylistButton_clicked(){
    QString playlistName = ui->lineEdit_name->text().trimmed();
    if (playlistName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Playlist name is required.");
        return;
    }

    Playlist newPlaylist(playlistName);
    for (QListWidgetItem* item : ui->listWidget_songs->selectedItems()) {
        QString text = item->text();
        for (const Song& song : songLibrary) {
            if (text.startsWith(song.getTitle())) {
                newPlaylist.addSong(song);
                break;
            }
        }
    }

    if (newPlaylist.getSongs().isEmpty()) {
        QMessageBox::warning(this, "Error", "Select at least one song.");
        return;
    }

    QFile file(playlistName + ".txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not save playlist.");
        return;
    }

    QTextStream out(&file);
    for (const Song& s : newPlaylist.getSongs())
        out << s.getTitle() << "," << s.getArtist() << "," << s.getAlbum() << "," << s.getDuration() << "\n";

    QMessageBox::information(this, "Success", "Playlist saved successfully.");
}

