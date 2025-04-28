#include "song.h"

Song::Song(QString name, QString songwriter, QString alb, QString time)
    : title(name), artist(songwriter), album(alb), duration(time) {}

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
