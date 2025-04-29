#include "playlistmanagement.h"
#include "ui_playlistmanagement.h"
#include "playlist.h"
#include "playlistcreator.h"
#include <QInputDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

PlaylistManagement::PlaylistManagement(QWidget *parent)
    : QDialog(parent), ui(new Ui::PlaylistManagement)
{
    ui->setupUi(this);
    loadFromFile("playlists.txt");
    //loadPlaylistsToText();
}

PlaylistManagement::~PlaylistManagement()
{
    delete ui;
}

Playlist* PlaylistManagement::getPlaylist(const QString &name)
{
    for (Playlist &p : playlists)
        if (p.getName() == name)
            return &p;
    return nullptr;
}

bool PlaylistManagement::saveToFile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return false;

    QTextStream out(&file);
    for (const Playlist& pl : playlists) {
        out << "#" << pl.getName() << "\n";
        for (const Song& s : pl.getSongs())
            out << s.getTitle() << "," << s.getArtist() << "," << s.getAlbum() << "," << s.getDuration() << "\n";
    }
    return true;
}

bool PlaylistManagement::loadFromFile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return false;

    QTextStream in(&file);
    Playlist *current = nullptr;
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.startsWith("#")) {
            playlists.append(Playlist(line.mid(1)));
            current = &playlists.last();
        } else if (current) {
            QStringList parts = line.split(",");
            if (parts.size() == 4)
                current->addSong(Song(parts[0], parts[1], parts[2], parts[3]));
        }
    }
    return true;
}

void PlaylistManagement::on_pushButton_back_clicked()
{
    this->close();
    if (parentWidget()) { //returns a pointer to the widget that opened the current window (checking to make sure a parent exists)
        parentWidget()->show(); //therefore can be used to go back
    }
}


void PlaylistManagement::on_createPlaylist_clicked()
{
    hide();
    PlaylistCreator *pc = new PlaylistCreator(this);
    pc->show();
}

