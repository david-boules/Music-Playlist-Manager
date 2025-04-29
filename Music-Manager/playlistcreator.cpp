#include "playlistcreator.h"
#include "ui_playlistcreator.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

PlaylistCreator::PlaylistCreator(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PlaylistCreator)
{
    ui->setupUi(this);
}

PlaylistCreator::~PlaylistCreator()
{
    delete ui;
}

void PlaylistCreator::loadSongs() {
    QFile file("songs.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");
        if (parts.size() == 4) {
            Song song = {parts[0], parts[1], parts[2], parts[3]};
            songLibrary.append(song);
            //ui->listWidget_songs->addItem(song.getTitle() + " - " + song.getArtist());
        }
    }
    file.close();
}

void PlaylistCreator::on_pushButton_back_clicked()
{
    this->close();
    if (parentWidget()) { //returns a pointer to the widget that opened the current window (checking to make sure a parent exists)
        parentWidget()->show(); //therefore can be used to go back
    }
}

