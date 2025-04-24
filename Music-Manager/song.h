#ifndef SONG_H
#define SONG_H

#include <QString>

class Song {
public:
    Song(QString name = "", QString songwriter = "", QString alb = "", QString time = "");
    QString getTitle() const;
    QString getArtist() const;
    QString getAlbum() const;
    QString getDuration() const;

    bool operator == (const Song& other) const;

private:
    QString title;
    QString artist;
    QString album;
    QString duration;

    //overloaded == operator to check for duplicates
};

#endif // SONG_H
