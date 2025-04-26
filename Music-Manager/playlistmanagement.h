#ifndef PLAYLISTMANAGEMENT_H
#define PLAYLISTMANAGEMENT_H

#include <QDialog>
#include <QVector>
#include <QLabel>
#include <QWidget>
#include "playlist.h"

namespace Ui {
class PlaylistManagement;
}

class PlaylistManagement : public QDialog
{
    Q_OBJECT

public:
    explicit PlaylistManagement(QWidget *parent = nullptr);
    ~PlaylistManagement();

private slots:
    void on_AddPlaylist_clicked();
    void on_DeletePlaylist_clicked();
    void on_AddSong_clicked();
    void on_DeleteSong_clicked();

    void on_pushButton_back_clicked();

private:
    Ui::PlaylistManagement *ui;

    QVector<Playlist> playlists;
    void loadPlaylistsToText();
    void refreshSongList(const Playlist &p);
    bool saveToFile(const QString &filename);
    bool loadFromFile(const QString &filename);
    Playlist* getPlaylist(const QString &name);
};

#endif // PLAYLISTMANAGEMENT_H
