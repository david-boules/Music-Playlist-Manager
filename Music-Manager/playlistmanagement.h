#ifndef PLAYLISTMANAGEMENT_H
#define PLAYLISTMANAGEMENT_H

#include <QDialog>
#include <QVector>
#include <QLabel>
#include <QListWidgetItem>
#include <QWidget>
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
    static const QVector<Playlist>& getUserPlaylist(const QString& username);
    static void addUserPlaylist(const QString& username, const Playlist& p);
    static void saveAllPlaylists();

    ~PlaylistManagement();

private slots:

    void on_pushButton_back_clicked();
    void on_createPlaylist_clicked();
    void on_listWidget_playlists_itemClicked(QListWidgetItem *item);

private:
    Ui::PlaylistManagement *ui;

    QString username;
    QVector<Playlist> playlists;
    static QMap<QString, QVector<Playlist>> AllPlaylists;

    void refreshSongList(const Playlist &p);
    bool saveToFile(const QString &filename);
    bool loadFromFile(const QString &filename);

    Playlist* getPlaylist(const QString &name);
};

#endif // PLAYLISTMANAGEMENT_H
