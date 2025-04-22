#ifndef PLAYLISTMANAGEMENT_H
#define PLAYLISTMANAGEMENT_H

#include <QDialog>
#include <QWidget>
#include <QVector>
#include <QString>
#include <QFile>
#include <QMessageBox>

#include <QInputDialog>
#include <QLabel>
#include "songpage.h"

namespace Ui {
class playlistmanagement;
}

class Song2 {
public:
    QString title, artist, duration;
    Song2(QString t = "", QString a = "", QString d = "") : title(t), artist(a), duration(d) {}
};



class Playlist {
public:
    QString name;
    QVector<Song2> songs;
    Playlist(QString n = "") : name(n) {}

    void addSong(const Song2 &song) { songs.push_back(song); }
    void deleteSong(const QString &title) {
        for (int i = 0; i < songs.size(); i++) {
            if (songs[i].title == title) {
                songs.removeAt(i);
                return;
            }
        }
    }
    int songCount() const {return songs.size();}
};

class PlaylistManager {
public:
    QVector<Playlist> playlists;

    bool loadFromFile(const QString &filename);
    bool saveToFile(const QString &filename);
    Playlist* getPlaylist(const QString &name);
};

class playlistmanagement : public QDialog
{
    Q_OBJECT

public:
    explicit playlistmanagement(QWidget *parent = nullptr);
    ~playlistmanagement();

private slots:
    void loadPlaylistsToText();
    void displaySongs();
    void addPlaylist();
    void deletePlaylist();
    void addSong2();
    void deleteSong();

    void on_AddPlaylist_clicked();

    void on_DeletePlaylist_clicked();

    void on_AddSong_clicked();

    void on_DeleteSong_clicked();

private:
    PlaylistManager manager;
    QLabel *playlistDisplay;
    QLabel *songDisplay;
    QString currentPlaylistName;

    void refreshSongList(const Playlist &p);
    Ui::playlistmanagement *ui;
};

#endif // PLAYLISTMANAGEMENT_H
