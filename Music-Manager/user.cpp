#include "playlistcreator.h"
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



using namespace std;

QMap<QString, QString> User:: usernames_and_passwords;

User::User(QString username, QString password, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::User)
{
    ui->setupUi(this);
    ui->label_welcome->setText("Welcome, " + username + "!");
}
User::~User()
{
    delete ui;
}

bool User::usernameExists(const QString& username) {
    return usernames_and_passwords.contains(username);
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

void User::on_userReports_clicked()
{
    hide();
    Reports *r = new Reports(this);
    r->show();
}

void User::on_searchSongs_clicked() {
    // Ask the user to input the song title to search for
    QString songToFind = QInputDialog::getText(this, "Search Songs", "Enter Song Title:");
    if (songToFind.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Song title is empty.");
        return;
    }

    // Determine the directory path where playlists are stored
    QString appPath = QCoreApplication::applicationDirPath();
    QDir dir(appPath);

    // Find all playlist files that belong to this user; the pattern matches UserName_*.txt "ALex_*.txt" with "Alex_Workout.txt"

    QStringList playlistFiles = dir.entryList(QStringList() << UserName + "_*.txt", QDir::Files);

    QStringList foundInPlaylists;

    bool found = false;

    // Search through each playlist file
    for (QString &fileName : playlistFiles) {
        QFile file(appPath + "/" + fileName);
        QTextStream in(&file);
        // Keep reading till the textstream end
        while (!in.atEnd()) {
          QString line = in.readLine().trimmed();
            if (line.contains(songToFind, Qt::CaseInsensitive)) // Check if the line contains the song title; ignore case.
            {
                found = true;
                foundInPlaylists.append(fileName);
                break;
            }
        }
        file.close();
    }

    // Display results to the user
    if (!found)
    {
        QMessageBox::information(this, "Not Found", "The song was not found in any of your playlists.");
    }
    else
    {
        QString message = "The song was found in:\n" + foundInPlaylists.join("\n");
        QMessageBox::information(this, "Song Found", message);
    }
}

void User::on_viewPlaylists_clicked() {
    hide();
    PlaylistManagement *pm = new PlaylistManagement(this);
    pm->show();
}

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

// type changed to int?? Or do we use QString??
int User::getAllPlaylists() {
    QDir dir(QCoreApplication::applicationDirPath()); //Get the path to the directory where the app is running

    //Find all files that match the pattern "UserName_*.txt"; assume playlists are stored as individual text files for each user
    QStringList files = dir.entryList(QStringList() << UserName + "_*.txt", QDir::Files);

    return files.count(); ;
}


void User::on_pushButton_back_clicked()
{
    this->close();
    if (parentWidget()) { //returns a pointer to the widget that opened the current window (checking to make sure a parent exists)
        parentWidget()->show(); //therefore can be used to go back
    }
}
