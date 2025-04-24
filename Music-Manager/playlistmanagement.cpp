#include "playlistmanagement.h"
#include "ui_playlistmanagement.h"
#include "playlist.h"
#include <QInputDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

PlaylistManagement::PlaylistManagement(QWidget *parent)
    : QDialog(parent), ui(new Ui::PlaylistManagement)
{
    ui->setupUi(this);
    loadFromFile("playlists.txt");
    loadPlaylistsToText();
}

PlaylistManagement::~PlaylistManagement()
{
    delete ui;
}

void PlaylistManagement::loadPlaylistsToText()
{
    QString display;
    for (const Playlist& p : playlists)
        display += p.getName() + " (" + QString::number(p.numSongs()) + " songs)\n";
    ui->playlistDisplay->setText(display);
}

void PlaylistManagement::refreshSongList(const Playlist &p)
{
    QString display;
    for (const Song& s : p.getSongs()) {
        display += s.getTitle() + " by " + s.getArtist() + " (" + s.getDuration() + ")\n";
    }
    ui->songDisplay->setText(display);
}

void PlaylistManagement::on_AddPlaylist_clicked()
{
    QString name = QInputDialog::getText(this, "Add Playlist", "Enter name:");
    if (name.isEmpty()) return;
    playlists.append(Playlist(name));
    saveToFile("playlists.txt");
    loadPlaylistsToText();
}

void PlaylistManagement::on_DeletePlaylist_clicked()
{
    QString name = QInputDialog::getText(this, "Delete Playlist", "Enter playlist name to delete:");
    for (int i = 0; i < playlists.size(); ++i) {
        if (playlists[i].getName() == name) {
            playlists.removeAt(i);
            break;
        }
    }
    saveToFile("playlists.txt");
    loadPlaylistsToText();
}

void PlaylistManagement::on_AddSong_clicked()
{
    QString name = QInputDialog::getText(this, "Playlist", "Enter playlist name:");
    Playlist* p = getPlaylist(name);
    if (!p) return;

    QString title = QInputDialog::getText(this, "Title", "Title:");
    QString artist = QInputDialog::getText(this, "Artist", "Artist:");
    QString album = QInputDialog::getText(this, "Album", "Album:");
    QString duration = QInputDialog::getText(this, "Duration", "Duration:");

    p->addSong(Song(title, artist, album, duration));
    saveToFile("playlists.txt");
    refreshSongList(*p);
}

void PlaylistManagement::on_DeleteSong_clicked()
{
    QString name = QInputDialog::getText(this, "Playlist", "Enter playlist name:");
    Playlist* p = getPlaylist(name);
    if (!p) return;

    QString title = QInputDialog::getText(this, "Delete Song", "Title to delete:");
    p->deleteSong(title);
    saveToFile("playlists.txt");
    refreshSongList(*p);
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
