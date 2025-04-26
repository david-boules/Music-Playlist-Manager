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
    void displaySongs();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_back_clicked();

private:
    Ui::SongPage *ui;
    QVector<Song> songLibrary;
};

#endif // SONGPAGE_H
