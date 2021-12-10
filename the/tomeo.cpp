//    ______
//   /_  __/___  ____ ___  ___  ____
//    / / / __ \/ __ `__ \/ _ \/ __ \
//   / / / /_/ / / / / / /  __/ /_/ /
//  /_/  \____/_/ /_/ /_/\___/\____/
//              video for sports enthusiasts...
//
//  2811 cw3 : twak 11/11/2021
//

#include <iostream>
#include <QApplication>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlaylist>
#include <string>
#include <vector>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtCore/QFileInfo>
#include <QtWidgets/QFileIconProvider>
#include <QDesktopServices>
#include <QImageReader>
#include <QMessageBox>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include "the_player.h"
#include "the_button.h"

#include <string>
#include <QLineEdit>
#include <QtWidgets>
#include <QFont>
#include <QRect>
#include "video_scroll.h"
#include "playlistswindow.h"
#include "playerwindow.h"
#include "sidebar.h"
#include "iconlabelcontainer.h"

int main(int argc, char *argv[]) {

    // let's just check that Qt is operational first
    qDebug() << "Qt version: " << QT_VERSION_STR << endl;

    // create the Qt Application
    QApplication app(argc, argv);
    // create the main window and layout
    QWidget window;
    window.setStyleSheet("background-color: #ffc070;");
    QHBoxLayout *primeWindow = new QHBoxLayout();
    window.setLayout(primeWindow);

    PlayerWindow videoWindow;
    videoWindow.assemble(argc, argv);

    PlaylistsWindow playlistWindow;
    playlistWindow.hide();

    window.setWindowTitle("Tomeo");
    window.setMinimumSize(1000, 680);
    ControlButton* menu = new ControlButton(new QWidget());
    menu->setStyleSheet("background-color:#ffe0ba");
    QHBoxLayout *menLay = new QHBoxLayout();
    //menu->setMaximumSize(30, 20);
    //menu->setMinimumSize(30, 20);
    menLay->setContentsMargins(0, 0, 0, 0);

    menLay->addWidget(menu);
    primeWindow->addLayout(menLay);


    SideBar * bar = new SideBar();
    bar->hide();
    bar->edit->hide();
    bar->playingNow->hide();

    menu->connect(menu, SIGNAL(clicked()), bar, SLOT (showIt()));
    menu->connect(menu, SIGNAL(clicked()), menu, SLOT (disapear()));
    bar->quit->connect(bar->quit, SIGNAL(clicked()), menu, SLOT (showIt()));
    bar->quit->connect(bar->quit, SIGNAL(clicked()), bar, SLOT (disapear()));

    bar->playingNow->connect(bar->playingNow, SIGNAL(clicked()), &playlistWindow, SLOT (disapear()));
    bar->playingNow->connect(bar->playingNow, SIGNAL(clicked()), &videoWindow, SLOT (showIt()));
    bar->playingNow->connect(bar->playingNow, SIGNAL(clicked()), bar->quit, SLOT (showIt()));
    bar->playingNow->connect(bar->playingNow, SIGNAL(clicked()), bar->edit, SLOT (disapear()));
    bar->playingNow->connect(bar->playingNow, SIGNAL(clicked()), bar->playingNow, SLOT (disapear()));
    bar->playingNow->connect(bar->playingNow, SIGNAL(clicked()), bar->playlists, SLOT (showIt()));

    bar->playlists->connect(bar->playlists, SIGNAL(clicked()), &playlistWindow, SLOT (showIt()));
    bar->playlists->connect(bar->playlists, SIGNAL(clicked()), &videoWindow, SLOT (disapear()));
    bar->playlists->connect(bar->playlists, SIGNAL(clicked()), bar->quit, SLOT (disapear()));
    bar->playlists->connect(bar->playlists, SIGNAL(clicked()), bar->edit, SLOT (showIt()));
    bar->playlists->connect(bar->playlists, SIGNAL(clicked()), bar->playingNow, SLOT (showIt()));
    bar->playlists->connect(bar->playlists, SIGNAL(clicked()), bar->playlists, SLOT (disapear()));

    //place side bar in seperate layout/widget
    primeWindow->addWidget(bar);
    primeWindow->addWidget(&videoWindow);
    primeWindow->addWidget(&playlistWindow);

    // showtime!
    window.show();

    // wait for the app to terminate
    return app.exec();
}
