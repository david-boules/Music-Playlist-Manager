#include "playlistmanagement.h"
#include "ui_playlistmanagement.h"
#include "playlist.h"
#include "playlistcreator.h"
#include <QInputDialog>
#include <QDir>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

PlaylistManagement::PlaylistManagement(QString username, QWidget *parent)
    : QDialog(parent), ui(new Ui::PlaylistManagement), username(username)
{
    ui->setupUi(this);
    ui->label_PMTitle->setText(username + "'s Playlist Management Page");
    connect(ui->listWidget_playlists, &QListWidget::itemClicked, this, &PlaylistManagement::on_listWidget_playlists_itemClicked);

    playlists = AllPlaylists[username];
    for(const Playlist& playlist : playlists) {
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

Playlist* PlaylistManagement::getPlaylist(const QString &name)
{
    for (Playlist &p : playlists)
        if (p.getName() == name)
            return &p;
    return nullptr;
}

void PlaylistManagement::addUserPlaylist(const QString& username, const Playlist& p) {
    AllPlaylists[username].append(p);
}

void PlaylistManagement::loadPlaylists() {
    QString basePath = QCoreApplication::applicationDirPath() + "/../../data/playlists";
    QDir dir(basePath);

#ifdef Q_OS_MAC
    if(!dir.exists()) {
        basePath = QCoreApplication::applicationDirPath() + "/../../../../../data/playlists";
        dir = QDir(basePath);
    }
#endif

    QStringList playlistFiles = dir.entryList(QStringList() << "*.txt", QDir::Files);

    for (const QString& fileName : playlistFiles) {
        QString username = fileName.section(".", 0, 0); // Extracting the username from the .txt file
        QFile file(dir.absoluteFilePath(fileName));
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) continue;

        QTextStream in(&file);
        Playlist* current = nullptr;
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (line.startsWith("#")) {                 // Playlist names will start with # in the .txt files
                current = new Playlist(line.mid(1));    // Removing the # when loading into system
                AllPlaylists[username].append(*current);
            } else if (current) {
                QStringList parts = line.split(",");
                if (parts.size() == 4)
                    current->addSong(Song(parts[0], parts[1], parts[2], parts[3]));
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

