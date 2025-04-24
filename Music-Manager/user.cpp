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
#include <QMessageBox>

using namespace std;

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

bool User::validateCredentials(const QString &username, const QString &password) {

    //usernames & passwords are hardcoded for now:
    QVector<QString> usernames = {"Alex", "Bob", "Charlie"};
    QVector<QString> passwords = {"Alex1234", "Bob123abc", "Charlie1"};
    for (qsizetype i = 0; i < usernames.size(); ++i) {
        if (usernames[i] == username && passwords[i] == password) {
            return true;
        }
    }
    return false;
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
