#ifndef PLAYLISTMANAGEMENT_H
#define PLAYLISTMANAGEMENT_H

#include <QDialog>
#include <QVector>
#include <QLabel>
#include <QListWidgetItem>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QWidget>
#include <QShowEvent>
#include "playlist.h"

namespace Ui {
class PlaylistManagement;
}

class PlaylistManagement : public QDialog
{
    Q_OBJECT

public:
    explicit PlaylistManagement(QString username, QWidget *parent = nullptr);
    static void loadPlaylists();
    static const QVector<Playlist>& getUserPlaylists(const QString& username);
    static void addUserPlaylist(const QString& username, const Playlist& p);
    static void saveAllPlaylists();
    int total_playlists() const;


    ~PlaylistManagement();

private slots:
    void on_pushButton_back_clicked();
    void showEvent(QShowEvent *event) override; // to update playlists in case of going back from playlist creation page
    void on_createPlaylist_clicked();
    void on_listWidget_playlists_itemClicked(QListWidgetItem *item);
    void on_AddSong_clicked();
    void on_DeleteSong_clicked();
    void on_RenamePlaylist_clicked();
    void on_DeletePlaylist_clicked();
    void on_SearchSong_clicked();
    void on_SearchPlaylist_clicked();

    void on_play_song_clicked();

    void on_pause_song_clicked();

private:
    Ui::PlaylistManagement *ui;

    QString username;
    QVector<Playlist>* playlists;
    static QMap<QString, QVector<Playlist>> AllPlaylists;

    void refreshSongList(const Playlist &p);
    bool saveToFile(const QString &filename);
    bool loadFromFile(const QString &filename);

    QMediaPlayer* player;
    QAudioOutput* audioOutput;

    Playlist* getPlaylist(const QString &name);
};

#endif // PLAYLISTMANAGEMENT_H
