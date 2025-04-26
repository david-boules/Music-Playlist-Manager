/*
To-Do:
- Implement 'back' button to go back to main window
- Fix 'validateCredentials' function to look for username/password matches in 'users.txt'
- Flesh-Out all user functions
 */

#include "playlistcreator.h"
#include "playlistmanagement.h"
#include "user.h"
#include "ui_user.h"
#include <fstream>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>

using namespace std;

QMap<QString, QString> User:: usernames_and_passwords;

User::User(QString username, QString password, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::User)
{
    ui->setupUi(this);
    ui->label_welcome->setText("Welcome " + username);
    ui->label_lastPlayedSong->setText("Last Played Song: " + getLastPlayedSong());
    ui->label_summary->setText("Total Playlists: " + getAllPlaylists());
}
User::~User()
{
    delete ui;
}

// Loading user info to the 'usernames_and_passwords' map at startup
void User::loadUsers() {
    QString filePath = QCoreApplication::applicationDirPath() + "/users.txt";
    QFile file(filePath);

    // Handling case for MacOS (file structure for reading .txt required is different)
    if (!file.exists()) {
#ifdef Q_OS_MAC
        filePath = QCoreApplication::applicationDirPath() + "/../../../../../users.txt"; //MacOS requires .txt files to be in the same directory as the executable (5 directories deeper than main project folder)
        file.setFileName(filePath);
#endif
    }

    qDebug() << "Trying to open:" << file.fileName();

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open users.txt for reading.";
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList parts = line.split(' ');
        if (parts.size() < 2) {
            qDebug() << "Invalid line format:" << line;
            continue;
        }

        QString username = parts[0];
        QString password = parts[1];

        usernames_and_passwords[username] = password;
    }

    file.close();
    qDebug() << "Loaded users:";
    for (auto it = usernames_and_passwords.begin(); it != usernames_and_passwords.end(); ++it) {
        qDebug() << "Username:" << it.key() << "Password:" << it.value();
    }
}

void User::saveUsers() {
    QString filePath = QCoreApplication::applicationDirPath() + "/users.txt";
    QFile file(filePath);

    if (!file.exists()) {
#ifdef Q_OS_MAC
        filePath = QCoreApplication::applicationDirPath() + "/../../../../../users.txt";
        file.setFileName(filePath);
#endif
    }

    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        qDebug() << "Cannot open users.txt for writing.";
        return;
    }

    QTextStream out(&file);
    for (auto it = usernames_and_passwords.begin(); it != usernames_and_passwords.end(); ++it) {
        out << it.key() << " " << it.value() << "\n";
    }

    file.close();
}

bool User::validateCredentials(const QString &username, const QString &password) {

    if(usernames_and_passwords.contains(username) && usernames_and_passwords[username] == password) {
        return true;
    } else {
        return false;
    }
}

void User::on_createPlaylist_clicked() {
    hide();
    PlaylistCreator *pc = new PlaylistCreator(this);
    pc->show();
}

void User::on_searchSongs_clicked() {
    QMessageBox::about(this, "Search", "Search Songs");
}

void User::on_viewPlaylist_clicked() {
    hide();
    PlaylistManagement *pm = new PlaylistManagement(this);
    pm->show();
}

QString User::getLastPlayedSong() {
    ifstream inputFile("grades.txt"); // Open the log file

    if (!inputFile.is_open()) {
        QMessageBox::warning(this, "Warning", "Could not open the file.");
        return "N/A";
    }

    string line;
    string prefix = UserName.toStdString() + "-LastPlayed:"; //create new copy the underlying string no

    // Search for a line that starts with "username-LastPlayed:"
    while (getline(inputFile, line)) {
        // Check if the line begins with "username-LastPlayed:"
        if (line.rfind(prefix, 0) == 0)  {
            size_t colonPos = line.find(':');
            if (colonPos != string::npos) {
                // Extract part after colon
                return QString::fromStdString(line.substr(colonPos + 1)); //Extract song name by returning what is after the colon
            }
        }
    }

    inputFile.close();
    return "N/A"; // If nothing found
}

// type must be changed
QString User::getAllPlaylists() {
    return "";
}
