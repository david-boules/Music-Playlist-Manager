#include "playlist.h"
#include <QString>

Playlist::Playlist(QString title) : name(title) {}

void Playlist::addSong(const Song& song) {
    songs.push_back(song);
}

void Playlist::deleteSong(const QString& title) {
    for (int i = 0; i < songs.size(); i++) {
        if (songs[i].getTitle() == title) {
            songs.removeAt(i);
            return;
        }
    }
}

QString Playlist::getName() const{
    return name;
}

const QVector<Song>& Playlist::getSongs() const {
    return songs;
}

int Playlist::numSongs() const {
    return songs.size();
}
