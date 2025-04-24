#include "songpage.h"
#include "ui_songpage.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

SongPage::SongPage(QWidget *parent)
    : QDialog(parent), ui(new Ui::SongPage)
{
    ui->setupUi(this);
    loadSongs();
    displaySongs();
}

SongPage::~SongPage()
{
    delete ui;
}

void SongPage::on_pushButton_clicked()
{
    QString title = ui->lineEdit_title->text().trimmed();
    QString artist = ui->lineEdit_artist->text().trimmed();
    QString album = ui->lineEdit_album->text().trimmed();

    if (title.isEmpty() || artist.isEmpty() || album.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields are required.");
        return;
    }

    Song newSong(title, artist, album);
    for (const Song& s : songLibrary) {
        if (s == newSong) {
            QMessageBox::warning(this, "Duplicate", "Song already exists.");
            return;
        }
    }

    songLibrary.append(newSong);
    saveSongs();
    displaySongs();

    ui->lineEdit_title->clear();
    ui->lineEdit_artist->clear();
    ui->lineEdit_album->clear();
}

void SongPage::loadSongs()
{
    QFile file("songs.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QStringList parts = in.readLine().split(",");
        if (parts.size() == 4)
            songLibrary.append(Song(parts[0], parts[1], parts[2], parts[3]));
    }
    file.close();
}

void SongPage::saveSongs()
{
    QFile file("songs.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QTextStream out(&file);
    for (const Song& s : songLibrary)
        out << s.getTitle() << "," << s.getArtist() << "," << s.getAlbum() << "\n";
    file.close();
}

void SongPage::displaySongs()
{
    ui->listWidget_songs->clear();
    for (const Song& s : songLibrary)
        ui->listWidget_songs->addItem(s.getTitle() + " - " + s.getArtist() + " [" + s.getAlbum() + "] (" + s.getDuration() + ")");
}
