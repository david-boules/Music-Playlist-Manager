#include "mainwindow.h"
#include "user.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    User::loadUsers(); //Users are loaded in at system startup

    MainWindow w;
    w.show();
    int terminate = a.exec();

    User::saveUsers(); // Contents of 'UsersList' saved to 'users.txt' when exiting the application

    return terminate;
}
