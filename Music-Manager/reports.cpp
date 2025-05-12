#include "reports.h"
#include "ui_reports.h"
#include <QFile>

Reports::Reports(User* current_user, PlaylistManagement* current_playlist, QWidget *parent)
    : QDialog(parent), ui(new Ui::Reports),user(current_user),playlist(current_playlist)
{
    ui->setupUi(this);
    ui->label_title->setText(user->get_username() + " 's Reports Page");
    ui->label_username->setText("Username: " + user->get_username());
    ui->label_totalPlaylists->setText("Total Playlists: " + QString::number(playlist->total_playlists()));

    displayPopularSongs();

}

Reports::~Reports()
{
    delete ui;
}

void Reports::displayPopularSongs() {
    const QVector<Playlist>& playlists = PlaylistManagement::getUserPlaylists(user->get_username());
    QList<Song> allSongs;

    for (const Playlist& playlist : playlists) {
        for (const Song& song : playlist.getSongs()) {
            allSongs.append(song);
        }
    }

    std::sort(allSongs.begin(), allSongs.end(), [](const Song& a, const Song& b) {
        return a.getPlayCount() > b.getPlayCount();
    });

    ui->tableWidget_mostPlayedSongs->clearContents();
    ui->tableWidget_mostPlayedSongs->setRowCount(qMin(3, allSongs.size()));
    ui->tableWidget_mostPlayedSongs->setColumnCount(3);
    ui->tableWidget_mostPlayedSongs->setHorizontalHeaderLabels({"Song", "Artist", "Plays"});

    ui->tableWidget_mostPlayedSongs->setColumnWidth(0, 180);
    ui->tableWidget_mostPlayedSongs->setColumnWidth(1, 120);
    ui->tableWidget_mostPlayedSongs->setColumnWidth(2, 50);

    for (int i = 0; i < qMin(3, allSongs.size()); ++i) {
        const Song& song = allSongs[i];
        ui->tableWidget_mostPlayedSongs->setItem(i, 0, new QTableWidgetItem(song.getTitle()));
        ui->tableWidget_mostPlayedSongs->setItem(i, 1, new QTableWidgetItem(song.getArtist()));
        ui->tableWidget_mostPlayedSongs->setItem(i, 2, new QTableWidgetItem(QString::number(song.getPlayCount())));
    }
}


QString Reports::getMostPlayedSongs() {
    QStringList topSongs;

    for (int i = 0; i < ui->tableWidget_mostPlayedSongs->rowCount(); ++i) {
        QString title = ui->tableWidget_mostPlayedSongs->item(i, 0)->text();
        QString artist = ui->tableWidget_mostPlayedSongs->item(i, 1)->text();
        QString plays = ui->tableWidget_mostPlayedSongs->item(i, 2)->text();

        topSongs << QString::number(i + 1) + ". " + title + " by " + artist + " (" + plays + " plays)";
    }

    return topSongs.isEmpty() ? "N/A" : topSongs.join("\n");
}

void Reports::on_pushButton_back_clicked()
{
    this->close();
    if (parentWidget()) { //returns a pointer to the widget that opened the current window (checking to make sure a parent exists)
        parentWidget()->show(); //therefore can be used to go back
    }
}

void Reports::on_export_txt_clicked()
{
    QString baseName = user->get_username() + "_report";
    QString basePath = QCoreApplication::applicationDirPath() + "/../../../data/reports/" + baseName + ".txt";

#ifdef Q_OS_MAC
    QFile macTest(basePath);
    if (!macTest.exists()) {
        basePath = QCoreApplication::applicationDirPath() + "/../../../../../data/reports/user_report.txt";
    }
#endif

    QFile file(basePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Export Failed", "Could not open TXT file for writing.");
        return;
    }

    QTextStream out(&file);
    out << "User Report\n";
    out << "\n";
    out << "Username: " << user->get_username() << "\n";
    out << "Total Playlists: " << playlist->total_playlists() << "\n";
    out << "Last Played Song: " << User::getLastPlayed(user->get_username()) << "\n\n";
    out << "Top Played Songs:\n";

    for (int i = 0; i < ui->tableWidget_mostPlayedSongs->rowCount(); ++i) {
        QString song = ui->tableWidget_mostPlayedSongs->item(i, 0)->text();
        QString artist = ui->tableWidget_mostPlayedSongs->item(i, 1)->text();
        QString plays = ui->tableWidget_mostPlayedSongs->item(i, 2)->text();

        out << QString::number(i + 1) << ". " << song << " by " << artist << " (" << plays << " plays)\n";
    }

    file.close();
    QMessageBox::information(this, "Export", ".txt report saved to data/reports.");
}


void Reports::on_export_csv_clicked()
{
    QString baseName = user->get_username() + "_report";
    QString basePath = QCoreApplication::applicationDirPath() + "/../../../data/reports/" + baseName + ".csv";


#ifdef Q_OS_MAC
    QFile macTest(basePath);
    if (!macTest.exists()) {
        basePath = QCoreApplication::applicationDirPath() + "/../../../../../data/reports/user_report.csv";
    }
#endif

    QFile file(basePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Export Failed", "Could not open CSV file for writing.");
        return;
    }

    QTextStream out(&file);
    out << "Total Playlists,Last Played Song,Song,Artist,Plays\n";

    for (int i = 0; i < ui->tableWidget_mostPlayedSongs->rowCount(); ++i) {
        QString song = ui->tableWidget_mostPlayedSongs->item(i, 0)->text();
        QString artist = ui->tableWidget_mostPlayedSongs->item(i, 1)->text();
        QString plays = ui->tableWidget_mostPlayedSongs->item(i, 2)->text();

        out << playlist->total_playlists() << ","
            << User::getLastPlayed(user->get_username()) << ","
            << song << "," << artist << "," << plays << "\n";
    }

    file.close();
    QMessageBox::information(this, "Export", ".csv report saved to data/reports.");
}
