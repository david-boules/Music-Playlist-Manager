#ifndef SONGPAGE_H
#define SONGPAGE_H

#include <QDialog>
#include <QListWidget>
#include <QVector>
#include "song.h"

namespace Ui {
class SongPage;
}

class SongPage : public QDialog
{
    Q_OBJECT

public:
    explicit SongPage(QWidget *parent = nullptr);
    ~SongPage();

    static const QVector<Song>& getSongLibrary();

    static void loadSongs(); // No need for a SongPage object to call this function (since it must be called at system startup)
    static void saveSongs(); // Same here (called when exiting the application)

private slots:

    void on_pushButton_back_clicked();

    void on_pushButton_displaySongs_clicked();

    void on_pushButton_addToSongLibrary_clicked();

    void on_pushButton_uploadArtwork_clicked();

private:
    Ui::SongPage *ui;
    static QVector<Song> songLibrary;
};

#endif // SONGPAGE_H
