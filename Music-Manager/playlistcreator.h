#ifndef PLAYLISTCREATOR_H
#define PLAYLISTCREATOR_H

#include <QDialog>
#include <QListWidget>
#include "song.h"

namespace Ui {
class PlaylistCreator;
}

class PlaylistCreator : public QDialog
{
    Q_OBJECT

public:
    explicit PlaylistCreator(const QString& username, QWidget *parent = nullptr);
    void loadSongs();
    void getSongs();

    ~PlaylistCreator();

private slots:
    void on_pushButton_back_clicked();

    void on_createPlaylist_clicked();

private:
    QString user;
    Ui::PlaylistCreator *ui;
    QVector<Song> songLibrary;
};

#endif // PLAYLISTCREATOR_H
