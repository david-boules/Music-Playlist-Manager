#include "song.h"

Song::Song(QString name, QString songwriter, QString alb, QString time, QString artPath, int count)
    : title(name), artist(songwriter), album(alb), duration(time), albumArtPath(artPath), playCount(count) {}

bool Song::operator==(const Song& other) const {
    return title == other.title && artist == other.artist;
}

QString Song:: getTitle() const{
    return title;
}

QString Song:: getArtist() const{
    return artist;
}

QString Song:: getAlbum() const{
    return album;
}

QString Song:: getDuration() const{
    return duration;
}

QString Song::getAlbumArtPath() const {
    return albumArtPath;
}

void Song::setAlbumArtPath(const QString& path) {
    albumArtPath = path;
}

int Song::getPlayCount() const {
    return playCount;
}

void Song::incrementPlayCount() {
    playCount++;
}

void Song::setPlayCount(int count) {
    playCount = count;
}
