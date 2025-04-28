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

    void loadSongs();
    void saveSongs();

private slots:

    void on_pushButton_back_clicked();

    void on_pushButton_displaySongs_clicked();

    void on_pushButton_addToSongLibrary_clicked();

private:
    Ui::SongPage *ui;
    QVector<Song> songLibrary;
};

#endif // SONGPAGE_H
