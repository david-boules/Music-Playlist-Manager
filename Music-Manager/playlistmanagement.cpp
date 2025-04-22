#include "playlistmanagement.h"
#include "ui_playlistmanagement.h"

playlistmanagement::playlistmanagement(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::playlistmanagement)
{
    ui->setupUi(this);
}

playlistmanagement::~playlistmanagement()
{
    delete ui;
}

void playlistmanagement::loadPlaylistsToText()
{
    QString display;
    for (int i = 0; i < manager.playlists.size(); i++)
    {
        const Playlist &p = manager.playlists[i];
        display += p.name + " (" + QString::number(p.songCount()) + " songs)\n";
    }
    playlistDisplay->setText(display);
}


void playlistmanagement::addPlaylist()
{
    QString name = QInputDialog::getText(this, "Add Playlist", "Enter playlist name:");
    if (name.isEmpty())
        return;
    manager.playlists.append(Playlist(name));
    manager.saveToFile("playlists.txt");
    loadPlaylistsToText();
}


void playlistmanagement::deletePlaylist()
{
    QString name = QInputDialog::getText(this, "Delete Playlist", "Enter playlist name to delete:");
    for (int i = 0; i < manager.playlists.size(); i++)
    {
        if (manager.playlists[i].name == name)
        {
            manager.playlists.removeAt(i);
            break;
        }
    }
    manager.saveToFile("playlists.txt");
    loadPlaylistsToText();
}

void playlistmanagement::refreshSongList(const Playlist &p) {
    QString display;
    for (int i = 0; i < p.songs.size(); i++) {
        const Song2 &s = p.songs[i];
        display += s.title + " by " + s.artist + " (" + s.duration + ")\n";
    }
    songDisplay->setText(display);
}

void playlistmanagement::addSong2()
{
    QString name = QInputDialog::getText(this, "Playlist", "Enter playlist name:");
   Playlist *p = manager.getPlaylist(name);
   if (!p)
    return;

    QString title = QInputDialog::getText(this, "Add Song", "Title:");
    QString artist = QInputDialog::getText(this, "Add Song", "Artist:");
    QString duration = QInputDialog::getText(this, "Add Song", "Duration:");

    p->addSong(Song2(title, artist, duration));
    manager.saveToFile("playlists.txt"); //fix error
    refreshSongList(*p);
}

void playlistmanagement::deleteSong()
{
    QString name = QInputDialog::getText(this, "Playlist", "Enter playlist name:");
   Playlist *p = manager.getPlaylist(name);
   if (!p)
       return;

   QString title = QInputDialog::getText(this, "Delete Song", "Title to delete:");
   p->deleteSong(title);
   manager.saveToFile("playlists.txt");
   refreshSongList(*p);
}

bool PlaylistManager::saveToFile(const QString &filename)
{
    QFile file(filename);

    QTextStream out(&file);
    for (int i = 0; i < playlists.size(); i++)
    {
        const Playlist &pl = playlists[i];
        out << "#" << pl.name << "\n";
        for (int j = 0; j < pl.songs.size(); j++)
        {
            const Song2 &s = pl.songs[j];
            out << s.title << "," << s.artist << "," << s.duration << "\n";
        }
    }
    return true;
}

Playlist* PlaylistManager::getPlaylist(const QString &name)
{
    for (int i = 0; i < playlists.size(); i++)
    {
        if (playlists[i].name == name)
            return &playlists[i];
    }
    return nullptr;
}

void playlistmanagement::displaySongs()
{
        QString name = QInputDialog::getText(this, "Display Songs", "Enter playlist name:");
        Playlist *p = manager.getPlaylist(name);
        if (p)
        {
            refreshSongList(*p);
        }
        else
        {
            QMessageBox::warning(this, "Error", "Playlist not found.");
        }
}

void playlistmanagement::on_AddPlaylist_clicked()
{
    addPlaylist();
}

void playlistmanagement::on_DeletePlaylist_clicked()
{
    deletePlaylist();
}

void playlistmanagement::on_AddSong_clicked()
{
    addSong2();

}

void playlistmanagement::on_DeleteSong_clicked()
{
    deleteSong();
}

