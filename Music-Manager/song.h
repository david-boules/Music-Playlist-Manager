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

    //overloaded == operator to check for duplicates
    bool operator == (const Song& other) const;

private:
    QString title;
    QString artist;
    QString album;
    QString duration;
};

#endif // SONG_H
