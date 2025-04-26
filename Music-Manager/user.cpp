#include "playlistcreator.h"
#include "playlistmanagement.h"
#include "reports.h"
#include "user.h"
#include "ui_user.h"
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
    ui->label_welcome->setText("Welcome, " + username + "! Last Played Song: " + getLastPlayedSong());
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

void User::on_createPlaylist_clicked() {
    hide();
    PlaylistCreator *pc = new PlaylistCreator(this);
    pc->show();
}

void User::on_userReports_clicked()
{
    hide();
    Reports *r = new Reports(this);
    r->show();
}

void User::on_searchSongs_clicked() {
    QMessageBox::about(this, "Search", "Search Songs");
}

void User::on_viewPlaylists_clicked() {
    hide();
    PlaylistManagement *pm = new PlaylistManagement(this);
    pm->show();
}

QString User::getLastPlayedSong() {
    //not working yet
        return "N/A";
    }

// type must be changed
QString User::getAllPlaylists() {
    //not working yet
    return "N/A";
}

void User::on_pushButton_back_clicked()
{
    this->close();
    if (parentWidget()) { //returns a pointer to the widget that opened the current window (checking to make sure a parent exists)
        parentWidget()->show(); //therefore can be used to go back
    }
}
