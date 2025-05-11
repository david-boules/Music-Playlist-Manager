#include "playlistmanagement.h"
#include "ui_playlistmanagement.h"
#include "playlist.h"
#include "playlistcreator.h"
#include "songpage.h"
#include <QInputDialog>
#include <QDir>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QShowEvent>

PlaylistManagement::PlaylistManagement(QString username, QWidget *parent)
    : QDialog(parent), ui(new Ui::PlaylistManagement), username(username)
{
    ui->setupUi(this);
    ui->label_PMTitle->setText(username + "'s Playlist Management Page");
    connect(ui->listWidget_playlists, &QListWidget::itemClicked, this, &PlaylistManagement::on_listWidget_playlists_itemClicked);

    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(50);

    playlists = &AllPlaylists[username];
    for (const Playlist &playlist : *playlists) {
        ui->listWidget_playlists->addItem(playlist.getName());
    }


    ui->tableWidget_songs->setColumnCount(4);
    ui->tableWidget_songs->setHorizontalHeaderLabels({"Title", "Artist", "Album", "Duration"});

    //loadPlaylistsToText();
}

PlaylistManagement::~PlaylistManagement()
{
    delete ui;
}

QMap<QString, QVector<Playlist>> PlaylistManagement::AllPlaylists;

void PlaylistManagement::showEvent(QShowEvent *event) {
    QDialog::showEvent(event);

    // Syncing with the latest playlists
    *playlists = AllPlaylists[username];

    ui->listWidget_playlists->clear();
    for (const Playlist& playlist : *playlists) {
        ui->listWidget_playlists->addItem(playlist.getName());
    }
}

Playlist* PlaylistManagement::getPlaylist(const QString &name)
{
    for (Playlist &p : *playlists)
        if (p.getName() == name)
            return &p;
    return nullptr;
}


void PlaylistManagement::addUserPlaylist(const QString& username, const Playlist& p) {
    AllPlaylists[username].append(p);

}


int PlaylistManagement::total_playlists() const {
    int count = 0;
    for (int i = 0; i < ui->listWidget_playlists->count(); ++i) {
        QListWidgetItem* item = ui->listWidget_playlists->item(i);
        if (item) count++;
    }
    return count;
}


void PlaylistManagement::loadPlaylists() {
    QString basePath = QCoreApplication::applicationDirPath() + "/../../../data/playlists";
    QDir dir(basePath);

#ifdef Q_OS_MAC
    if(!dir.exists()) {
        basePath = QCoreApplication::applicationDirPath() + "/../../../../../data/playlists";
        dir = QDir(basePath);
    }
#endif

    QStringList playlistFiles = dir.entryList(QStringList() << "*.txt", QDir::Files);

    for (const QString& fileName : playlistFiles) {

        QString username = fileName.section(".", 0, 0); // Extracting the username from the .txt filename
        QFile file(dir.absoluteFilePath(fileName));
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) continue;

        QTextStream in(&file);
        Playlist* current = nullptr;

        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();

            if (line.startsWith("#")) {                 // Playlist names will start with # in the .txt files

                if(current) {
                    AllPlaylists[username].append(*current);
                    delete current;
                }
                current = new Playlist(line.mid(1));    // Removing the # when loading into system

            } else if (current) {
                QStringList parts = line.split(",");
                if (parts.size() == 4)
                    current->addSong(Song(parts[0], parts[1], parts[2], parts[3]));
            }
        }

        if(current) {
            AllPlaylists[username].append(*current);
            delete current;
        }

        file.close();
    }
}

/*
void PlaylistManagement::saveAllPlaylists() {
    for(auto it = AllPlaylists.begin(); it != AllPlaylists.end(); it++) {
        QString username = it.key();
        QString filePath = QCoreApplication::applicationDirPath() + "/../../../data/playlists/" + username + "Playlists.txt";

#ifdef Q_OS_MAC
        if (!QFile::exists(filePath)) {
            filePath = QCoreApplication::applicationDirPath() + "/../../../../../data/playlists/" + username + ".txt";
        }
#endif
        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            continue;

        QTextStream output(&file);
        for(const Playlist&playlist : it.value()) {
            output << "#" << playlist.getName() << "\n";
            for(const Song&song : playlist.getSongs()) {
                output << song.getTitle() << "," << song.getArtist() << "," << song.getAlbum() << "," << song.getDuration() << "\n";
            }
        }

        file.close();
    }
}
*/


void PlaylistManagement::saveAllPlaylists() {
    QString basePath = QCoreApplication::applicationDirPath() + "/../../../data/playlists/";

#ifdef Q_OS_MAC
    QDir macTest(basePath);
    if (!macTest.exists()) {
        basePath = QCoreApplication::applicationDirPath() + "/../../../../../data/playlists/";
    }
#endif

    for (auto it = AllPlaylists.begin(); it != AllPlaylists.end(); it++) {
        QString username = it.key();
        QString filePath = basePath + username + ".txt";  // Match the filename format used in loadPlaylists()

        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            continue;

        QTextStream output(&file);
        for (const Playlist &playlist : it.value()) {
            output << "#" << playlist.getName() << "\n";
            for (const Song &song : playlist.getSongs()) {
                output << song.getTitle() << "," << song.getArtist() << "," << song.getAlbum() << "," << song.getDuration() << "\n";
            }
        }

        file.close();
    }
}


const QVector<Playlist>& PlaylistManagement::getUserPlaylist(const QString& username){
    return AllPlaylists[username];

}

void PlaylistManagement::on_pushButton_back_clicked()
{
    this->close();
    if (parentWidget()) { //returns a pointer to the widget that opened the current window (checking to make sure a parent exists)
        parentWidget()->show(); //therefore can be used to go back
    }
}


void PlaylistManagement::on_createPlaylist_clicked()
{
    hide();
    PlaylistCreator *pc = new PlaylistCreator(username, this);
    pc->show();

    *playlists = AllPlaylists[username];
    ui->listWidget_playlists->clear();

    for(const Playlist& playlist : *playlists)
        ui->listWidget_playlists->addItem(playlist.getName());
}


void PlaylistManagement::on_listWidget_playlists_itemClicked(QListWidgetItem *item)
{
    QString name = item->text();
    Playlist* p = getPlaylist(name);

    if(!p) return;

    ui->tableWidget_songs->clear();
    ui->tableWidget_songs->setColumnCount(4);
    ui->tableWidget_songs->setRowCount(p->getSongs().size());
    ui->tableWidget_songs->setHorizontalHeaderLabels({"Title", "Artist", "Album", "Duration"});

    for(int i = 0; i < p->getSongs().size(); i++) {
        const Song& song = p->getSongs()[i];
        ui->tableWidget_songs->setItem(i, 0, new QTableWidgetItem(song.getTitle()));
        ui->tableWidget_songs->setItem(i, 1, new QTableWidgetItem(song.getArtist()));
        ui->tableWidget_songs->setItem(i, 2, new QTableWidgetItem(song.getAlbum()));
        ui->tableWidget_songs->setItem(i, 3, new QTableWidgetItem(song.getDuration()));

    }
}

void PlaylistManagement::on_AddSong_clicked() {

    QListWidgetItem* currentItem = ui->listWidget_playlists->currentItem();
    if (!currentItem) {
        QMessageBox::warning(this, "No Playlist", "Please select a playlist to add a song.");
        return;
    }

    Playlist* p = getPlaylist(currentItem->text());
    if (!p)
        return;

    QString title = QInputDialog::getText(this, "Add Song", "Enter Song Title:");
    if (title.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Error", "Song title cannot be empty.");
        return;
    }

    const QVector<Song>& library = SongPage::getSongLibrary();
    bool found = false;
    Song foundSong;

    // Checking if the song is in the song library
    for (const Song& song : library) {
        if (song.getTitle().compare(title, Qt::CaseInsensitive) == 0) { // Case-Insensitivity for adding songs
            foundSong = song;
            found = true;
            break;
        }
    }
    if (!found) {
        QMessageBox::warning(this, "Not Found", "Song not found in library.");
        return;
    }

    // Prevent adding a duplicate song
    for (const Song& s : p->getSongs()) {
        if (s == foundSong) {
            QMessageBox::warning(this, "Duplicate Song", "This song already exists in the playlist.");
            return;
        }
    }

    // Add the song to the playlist
    p->addSong(foundSong);
    on_listWidget_playlists_itemClicked(currentItem); // Refresh view
}

void PlaylistManagement::on_DeleteSong_clicked() {
    QListWidgetItem* currentItem = ui->listWidget_playlists->currentItem();
    if (!currentItem) {
        QMessageBox::warning(this, "Error", "No playlist selected");
        return;
    }
    Playlist* p = getPlaylist(currentItem->text());
    if (!p)
        return;

    int row = ui->tableWidget_songs->currentRow();
    if (row < 0 || row >= p->getSongs().size()) {
        QMessageBox::warning(this, "Error", "No song selected");
        return;
    }

    // To prevent deleting the last song and having an empty playlist
    if (p->getSongs().size() == 1) {
        QMessageBox::warning(this, "Not Allowed", "Playlists must contain at least one song.");
        return;
    }

    p->removeSong(row);
    // Refresh the view
    on_listWidget_playlists_itemClicked(currentItem);
}


void PlaylistManagement::on_RenamePlaylist_clicked() {
    QListWidgetItem* currentItem = ui->listWidget_playlists->currentItem();
    if (!currentItem)
        return;

    Playlist* p = getPlaylist(currentItem->text());
    if (!p) return;

    QString newName = QInputDialog::getText(this, "Rename Playlist", "New Name:").trimmed();
    if (newName.isEmpty()) {
        QMessageBox::warning(this, "Empty Name", "Playlist name cannot be empty");
        return;
    }

    for (const Playlist& existingPlaylist : *playlists) {
        if (existingPlaylist.getName() == newName && &existingPlaylist != p) {
            QMessageBox::warning(this, "Duplicate Name", "A playlist with the name\"" + newName + "\" already exists.");
            return;
        }
    }

    p->setName(newName);
    currentItem->setText(newName);
}

void PlaylistManagement::on_DeletePlaylist_clicked() {
    QListWidgetItem* currentItem = ui->listWidget_playlists->currentItem();
    if (!currentItem) {
        QMessageBox::warning(this, "No Playlist Selected", "Please select a playlist to delete.");
        return;
    }

    QString playlistName = currentItem->text();

    QMessageBox::StandardButton confirm = QMessageBox::question(
        this, "Confirm Deletion", "Are you sure you want to delete the playlist \"" + playlistName + "\"?",
        QMessageBox::Yes | QMessageBox::No);

    if (confirm == QMessageBox::No)
        return;

    // Remove playlist from vector
    for (int i = 0; i < playlists->size(); i++) {
        if ((*playlists)[i].getName() == playlistName) {
            playlists->remove(i);
            break;
        }
    }

    // Remove from UI
    delete currentItem;

    // Clear songs table
    ui->tableWidget_songs->clearContents();
    ui->tableWidget_songs->setRowCount(0);

    QMessageBox::information(this, "Deleted", "Playlist \"" + playlistName + "\" is deleted.");
}


void PlaylistManagement::on_SearchSong_clicked()
{

}

void PlaylistManagement::on_SearchPlaylist_clicked()
{
    QString name = QInputDialog::getText(this, "Search Playlist", "Enter Playlist Name:");
    if (name.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a playlist name.");
        return;
    }

    // Loop through items in the list widget
    bool found = false;
    for (int i = 0; i < ui->listWidget_playlists->count(); ++i) {
        QListWidgetItem* item = ui->listWidget_playlists->item(i);
        if (item->text().compare(name, Qt::CaseInsensitive) == 0) {
            // Highlight the found playlist
            ui->listWidget_playlists->setCurrentItem(item);
            on_listWidget_playlists_itemClicked(item);  // auto-load songs
            found = true;
            break;
        }
    }

    if (!found) {
        QMessageBox::information(this, "Not Found", "No playlist named \"" + name + "\" was found.");
    }
}


void PlaylistManagement::on_play_song_clicked() {
    QListWidgetItem* selectedPlaylist = ui->listWidget_playlists->currentItem();
    int selectedRow = ui->tableWidget_songs->currentRow();

    if (!selectedPlaylist || selectedRow < 0) {
        QMessageBox::warning(this, "Selection Error", "Please select a playlist and a song.");
        return;
    }

    Playlist* playlist = getPlaylist(selectedPlaylist->text());
    if (!playlist || selectedRow >= playlist->getSongs().size()) return;

    QString songTitle = playlist->getSongs()[selectedRow].getTitle().trimmed();
    QString songPath = QCoreApplication::applicationDirPath() + "/../../../data/songs/" + songTitle + ".mp3";

    #ifdef Q_OS_MAC
    if (!QFile::exists(songPath))
        songPath = QCoreApplication::applicationDirPath() + "/../../../../../data/songs/" + songTitle + ".mp3";
    #endif

    if (!QFile::exists(songPath)) {
        QMessageBox::warning(this, "File Error", "MP3 file not found for song: " + songTitle);
        return;
    }

    player->setSource(QUrl::fromLocalFile(songPath));
    player->play();

    QMessageBox::information(this, "Now Playing", "🎵 " + songTitle);
}


void PlaylistManagement::on_pause_song_clicked()
{
    player->pause();
}

