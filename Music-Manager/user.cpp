#include "playlistmanagement.h"
#include "reports.h"
#include "user.h"
#include "ui_user.h"
#include <QInputDialog>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QDir> //To search, filter, and list files in directory.
#include <QTextStream>
#include <QCoreApplication> //To access the path where the application is running (e.g., the folder containing the .exe or .app file).
#include <QDebug>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QAudioOutput>

using namespace std;

QMap<QString, UserInfo> User::UsersList;

User::User(QString username, QString password, PlaylistManagement* playlist, QWidget *parent) : QDialog(parent) , ui(new Ui::User),playlist1(playlist)
{
    ui->setupUi(this);


    ui->label_welcome->setText("Welcome, " + username + "!");
    ui->label_totalPlaylists->setText("Total Playlists :" +QString::number(playlist1->total_playlists()) );

    UserName = username;
    Password = password;

    QString lastPlayed = User::getLastPlayed(UserName);
    ui->label_lastPlayedSong->setText("Last Played: " + lastPlayed);
    ui->label_lastPlaylistAccessed->setText("Last Playlist: " + getLastPlaylist(UserName));


}

QMap<QString, QString> User::LastPlayedMap;
QMap<QString, QString> User::LastPlaylistMap;

User::~User()
{
    delete ui;
}

/* Functions concerning User Storage
 * usernameExists
 * loadUsers
 * saveUsers
 * validateCredentials
 * addUser
 * deleteUser
 * getUserRole
 */

// Check for existing username
bool User::usernameExists(const QString& username) {
    return UsersList.contains(username);
}

// Loading user info from 'users.txt' to the 'UsersList' map at startup
void User::loadUsers() {
    QString filePath = QCoreApplication::applicationDirPath() + "/../../../data/users.txt";
    QFile file(filePath);

    // Handling case for MacOS (file structure for reading .txt required is different)
    if (!file.exists()) {
#ifdef Q_OS_MAC
        filePath = QCoreApplication::applicationDirPath() + "/../../../../../data/users.txt"; //MacOS requires .txt files to be in the same directory as the executable (5 directories deeper than main project folder)
        file.setFileName(filePath);
#endif
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();


        if (line.isEmpty()) continue;

        QStringList fields = line.split(' ');

        if (fields.size() < 4) continue;

        UserInfo info;
        info.password = fields[1];
        info.email = fields[2];
        info.role = fields[3];
        UsersList[fields[0]] = info;
    }
    file.close();
}

// Writing user info to 'users.txt' when exiting the application
void User::saveUsers() {
    QString filePath = QCoreApplication::applicationDirPath() + "/../../../data/users.txt";
    QFile file(filePath);

    if (!file.exists()) {
#ifdef Q_OS_MAC
        filePath = QCoreApplication::applicationDirPath() + "/../../../../../data/users.txt";
        file.setFileName(filePath);
#endif
    }

    if (!file.open(QIODevice::WriteOnly | QFile::Text | QIODevice::Truncate)) { // 'Truncate' to ensure file is completely cleared and rewritten
        return;
    }

    QTextStream out(&file);
    for (auto it = UsersList.begin(); it != UsersList.end(); it++) {
        out << it.key() << " " << it.value().password << " " << it.value().email << " " << it.value().role << "\n";
    }

    file.close();
}

void User::loadLastPlayedSongs() {
    QString path = QCoreApplication::applicationDirPath() + "/../../../data/lastPlayed.txt";
#ifdef Q_OS_MAC
    if (!QFile::exists(path))
        path = QCoreApplication::applicationDirPath() + "/../../../../../data/lastPlayed.txt";
#endif

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QStringList parts = line.split(' ', Qt::SkipEmptyParts);
        if (parts.size() >= 2)
            LastPlayedMap[parts[0]] = parts.mid(1).join(" ");  // song may contain spaces
    }
    file.close();
}

void User::saveLastPlayedSongs() {
    QString path = QCoreApplication::applicationDirPath() + "/../../../data/lastPlayed.txt";
#ifdef Q_OS_MAC
    path = QCoreApplication::applicationDirPath() + "/../../../../../data/lastPlayed.txt";
#endif

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QTextStream out(&file);
    for (auto it = LastPlayedMap.begin(); it != LastPlayedMap.end(); ++it) {
        out << it.key() << " " << it.value().trimmed() << "\n";
    }
    file.close();
}

// Checking whehter the right username and password have been entered
bool User::validateCredentials(const QString &username, const QString &password) {

    if(UsersList.contains(username) && UsersList[username].password == password) {
        return true;
    } else {
        return false;
    }
}

// Function that doubles as a boolean to check if admin wants to add a user and adds the user accordingly
bool User::addUser(const QString& username, const QString& password, const QString& email, const QString& role) {

    if (UsersList.contains(username)) {
        return false;
    }

    UserInfo info = {password, email, role};
    UsersList[username] = info;
    return true;
}

// Function that doubles as a boolean to check if admin wants to delete a user and deletes the user accordingly
bool User::deleteUser(const QString& username, const QString& password) {

    if (!UsersList.contains(username) || UsersList[username].password != password) {
        return false;
    }

    UsersList.remove(username);
    return true;
}

// Getter function to get a user's role to handle login
QString User::getUserRole(const QString& username) {
    return UsersList[username].role;
}

// Getter function to get the 'UsersList' data structure for operations
QMap<QString, UserInfo> User::getAllUsers() {
    return UsersList;
}


/* Functions for user dashboard functionality
 * getLastPlayedSong
 * getAllPlaylists
 */

QString User::getLastPlayedSong() {
    //Create the filename where last played songs are stored for this user
    QFile file(UserName + ".txt");

    QTextStream in(&file); //Textstream to read the file
    QString last;

    // Read the file line by line; each line is assumed to be a song title
    while (!in.atEnd()) {
        last = in.readLine().trimmed(); // Keep updating 'last' with the newest line
    }

    // If the file is empty, return "N/A"
    return last.isEmpty() ? "N/A" : last;
}

void User::setLastPlayed(const QString& username, const QString& song) {
    LastPlayedMap[username] = song.trimmed();
}

QString User::getLastPlayed(const QString& username) {
    return LastPlayedMap.value(username, "N/A");
}

void User::setLastPlaylist(const QString& username, const QString& playlist) {
    LastPlaylistMap[username] = playlist.trimmed();
}

QString User::getLastPlaylist(const QString& username) {
    return LastPlaylistMap.value(username, "N/A");
}

void User::loadLastPlaylist() {
    QString path = QCoreApplication::applicationDirPath() + "/../../../data/lastPlaylist.txt";
#ifdef Q_OS_MAC
    if (!QFile::exists(path))
        path = QCoreApplication::applicationDirPath() + "/../../../../../data/lastPlaylist.txt";
#endif

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QStringList parts = line.split(' ', Qt::SkipEmptyParts);
        if (parts.size() >= 2)
            LastPlaylistMap[parts[0]] = parts.mid(1).join(" ");
    }
    file.close();
}

void User::saveLastPlaylist() {
    QString path = QCoreApplication::applicationDirPath() + "/../../../data/lastPlaylist.txt";
#ifdef Q_OS_MAC
    path = QCoreApplication::applicationDirPath() + "/../../../../../data/lastPlaylist.txt";
#endif

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QTextStream out(&file);
    for (auto it = LastPlaylistMap.begin(); it != LastPlaylistMap.end(); ++it) {
        out << it.key() << " " << it.value().trimmed() << "\n";
    }
    file.close();
}


/* Functions for page navigation / pop-ups
 * on_userReports_clicked
 * on_searchSongs_clicked
 * on_viewPlaylists_clicked
 * on_pushButton_back_clicked
 */
void User::on_userReports_clicked()
{
    hide();
    PlaylistManagement* p = new PlaylistManagement(UserName);  // or however you build it
    Reports *r = new Reports(this, p,this);
    r->show();
}

void User::on_searchSongs_clicked() {
    QString songToFind = QInputDialog::getText(this, "Search Songs", "Enter Song Title:");
    if (songToFind.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Song title is empty.");
        return;
    }

    const QVector<Playlist>& userPlaylists = PlaylistManagement::getUserPlaylists(UserName);
    QStringList foundIn;

    for (const Playlist& playlist : userPlaylists) {
        for (const Song& song : playlist.getSongs()) {
            if (song.getTitle().compare(songToFind, Qt::CaseInsensitive) == 0) {
                foundIn.append(playlist.getName());
                break;
            }
        }
    }

    if (foundIn.isEmpty()) {
        QMessageBox::information(this, "Not Found", "The song \"" + songToFind + "\" was not found in any of your playlists.");
    } else {
        QString message = "The song \"" + songToFind + "\" was found in the following playlist(s):\n" + foundIn.join("\n");
        QMessageBox::information(this, "Song Found", message);
    }
}


void User::on_viewPlaylists_clicked() {
    hide();
    PlaylistManagement *pm = new PlaylistManagement(UserName, this);
    pm->show();
}

void User::on_pushButton_back_clicked()
{
    this->close();
    if (parentWidget()) { //returns a pointer to the widget that opened the current window (checking to make sure a parent exists)
        parentWidget()->show(); //therefore can be used to go back
    }
}

void User::showEvent(QShowEvent* event) {
    QDialog::showEvent(event); // Always call base implementation first

    int count = playlist1->total_playlists();
    ui->label_totalPlaylists->setText("Total Playlists: " + QString::number(count));

    QString lastPlayed = User::getLastPlayed(UserName);
    ui->label_lastPlayedSong->setText("Last Played: " + lastPlayed);
}
