#include "reports.h"
#include "ui_reports.h"

Reports::Reports(User* current_user, PlaylistManagement* current_playlist, QWidget *parent)
    : QDialog(parent), ui(new Ui::Reports),user(current_user),playlist(current_playlist)
{
    ui->setupUi(this);
     ui->label_2->setText("Username: " + user->get_username() + "!");
    ui->label_3->setText("Total playlist created : " + QString::number(playlist->total_playlists()) + "!");

}

Reports::~Reports()
{
    delete ui;
}

void Reports::on_pushButton_back_clicked()
{
    this->close();
    if (parentWidget()) { //returns a pointer to the widget that opened the current window (checking to make sure a parent exists)
        parentWidget()->show(); //therefore can be used to go back
    }
}

void Reports::on_pushButton_clicked()
{

}

