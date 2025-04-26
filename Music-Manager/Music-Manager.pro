QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TEMPLATE = app
TARGET = MusicPlaylistManager

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    main.cpp \
    mainwindow.cpp \
    playlist.cpp \
    playlistcreator.cpp \
    playlistmanagement.cpp \
    reports.cpp \
    song.cpp \
    songpage.cpp \
    user.cpp

HEADERS += \
    admin.h \
    mainwindow.h \
    playlist.h \
    playlistcreator.h \
    playlistmanagement.h \
    reports.h \
    song.h \
    songpage.h \
    user.h

FORMS += \
    admin.ui \
    mainwindow.ui \
    playlistcreator.ui \
    playlistmanagement.ui \
    reports.ui \
    songpage.ui \
    user.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
