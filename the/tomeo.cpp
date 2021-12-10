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
    QHBoxLayout *menLay = new QHBoxLayout();
    menLay->setContentsMargins(0, 0, 0, 0);

    primeWindow->addLayout(menLay);


    SideBar * bar = new SideBar();

    // bar->quit->connect(bar->quit, SIGNAL(clicked()), bar, SLOT(disapear()));

    bar->playingNow->connect(bar->playingNow, SIGNAL(clicked()), &playlistWindow, SLOT (disapear()));
    bar->playingNow->connect(bar->playingNow, SIGNAL(clicked()), &videoWindow, SLOT (showIt()));

    bar->playlists->connect(bar->playlists, SIGNAL(clicked()), &playlistWindow, SLOT (showIt()));
    bar->playlists->connect(bar->playlists, SIGNAL(clicked()), &videoWindow, SLOT (disapear()));

    //place side bar in seperate layout/widget
    primeWindow->addWidget(bar);
    primeWindow->addWidget(&videoWindow);
    primeWindow->addWidget(&playlistWindow);

    // showtime!
    window.show();

    // wait for the app to terminate
    return app.exec();
}
