#include "songpage.h"
#include "ui_songpage.h"
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QString>

SongPage::SongPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SongPage)
{
    ui->setupUi(this);
    songs.loadSongs();
    songs.displaySongsInListWidget(ui->listWidget_songs);

}

SongPage::~SongPage()
{
    delete ui;
}
Songs::Songs(){
    head=NULL;
}

void Songs::addSong(QString title, QString artist, QString album){

    Song* temp=head;
    while(temp!=nullptr){
        if(temp->title==title){
            QMessageBox::warning(nullptr,"alert", "dublicated");
            return;
        }
        temp=temp->next;
    }



    Song* newSong = new Song{title, artist, album, NULL};

    if (!head) {
        head = newSong;
    } else {
        Song* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newSong;
    }

}
void Songs::displaySongsInListWidget(QListWidget* listWidget){
    listWidget->clear();
    Song* temp = head;
    while (temp != nullptr) {
        QString songInfo = temp->title + " - " + temp->artist + " [" + temp->album + "]";
        listWidget->addItem(songInfo);  // Add song info to the list
        temp = temp->next;

}
}

void Songs::saveSongs(){
    QFile writeFile("D:/my/home/Zezo/Music-Playlist-Manager/Music-Manager/songs.txt");
    if (!writeFile.open(QFile::WriteOnly | QFile::Text )){
            QMessageBox::warning(NULL, "Warning", "Could not open the file.");
        return;}


    QTextStream out(&writeFile);
    Song* temp = head;
    while (temp != nullptr ) {

        out << temp->title << "," << temp->artist << "," << temp->album << "\n";
        temp=temp->next;
    }


    writeFile.flush();
    writeFile.close();
}
void Songs::loadSongs(){
    QFile readFile("D:/my/home/Zezo/Music-Playlist-Manager/Music-Manager/songs.txt");
    if (!readFile.open(QFile::ReadOnly | QFile::Text )){
        QMessageBox::warning(NULL, "Warning", "Could not open the file.");
        return;}

    QTextStream in(&readFile);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QStringList parts = line.split(',');

        if (parts.size() == 3) {
            addSong(parts[0], parts[1], parts[2]);
        }
    }
}




void SongPage::on_pushButton_clicked()
{
    QString title = ui->lineEdit_title->text();
    QString artist = ui->lineEdit_artist->text();
    QString album = ui->lineEdit_album->text();

    if (title.isEmpty() || artist.isEmpty() || album.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields are required.");
        return;
    }



    songs.addSong(title, artist,album);
    songs.displaySongsInListWidget(ui->listWidget_songs);
   songs.saveSongs();




    ui->lineEdit_title->clear();
    ui->lineEdit_artist->clear();
    ui->lineEdit_album->clear();

};








