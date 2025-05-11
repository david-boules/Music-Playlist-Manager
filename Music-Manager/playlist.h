#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "song.h"
#include <QString>
#include <QVector>

class Playlist
{
public:
    Playlist(QString title = "");

    void addSong(const Song& song);
    void deleteSong(const QString &title);
    int numSongs() const;

    void removeSong(int index);
    void setName(const QString& _name);


    QString getName() const;
    const QVector<Song>& getSongs() const; // Non-const since play counts need to be updated
    QVector<Song>& getSongsIncrement();

private:
    QString name;
    QVector<Song> songs;
};

#endif // PLAYLIST_H
