#ifndef SONGPAGE_H
#define SONGPAGE_H

#include <QDialog>
#include <QList>
#include <QListWidget>


namespace Ui {
class SongPage;
}
struct Song {
    QString title;
    QString artist;
    QString album;
    Song* next;
};
class Songs {
public:
    Song* head;

    Songs();


    void addSong(QString title, QString artist, QString album);

    void displaySongsInListWidget(QListWidget* listWidget);

    void saveSongs();

    void loadSongs();
};


class SongPage : public QDialog
{
    Q_OBJECT

public:
    explicit SongPage(QWidget *parent = nullptr);
    ~SongPage();

private slots:
    void on_pushButton_clicked();



private:
    Ui::SongPage *ui;
    Songs songs;
};

#endif // SONGPAGE_H
