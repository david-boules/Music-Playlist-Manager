#ifndef PLAYLISTCREATOR_H
#define PLAYLISTCREATOR_H

#include <QDialog>
#include <QListWidget>
#include "song.h"
#include "playlist.h"

namespace Ui {
class PlaylistCreator;
}

class PlaylistCreator : public QDialog
{
    Q_OBJECT

public:
    explicit PlaylistCreator(QWidget *parent = nullptr);
    void loadSongs();
    void getSongs();

    ~PlaylistCreator();

private slots:
    void on_createPlaylistButton_clicked();

    void on_pushButton_back_clicked();

private:
    Ui::PlaylistCreator *ui;
    QVector<Song> songLibrary;
};

#endif // PLAYLISTCREATOR_H
