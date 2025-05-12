#ifndef REPORTS_H
#define REPORTS_H

#include <QDialog>
#include "user.h"
#include "playlistmanagement.h"

namespace Ui {
class Reports;
}

class Reports : public QDialog
{
    Q_OBJECT

public:
    explicit Reports(User* current_user,PlaylistManagement* current_playlist, QWidget *parent = nullptr);

    QString getMostPlayedSongs();
    void displayPopularSongs();

    ~Reports();

private slots:
    void on_pushButton_back_clicked();

    void on_export_txt_clicked();

    void on_export_csv_clicked();

private:
    Ui::Reports *ui;
    User* user;
    PlaylistManagement* playlist;
};

#endif // REPORTS_H
