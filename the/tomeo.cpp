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

// read in videos and thumbnails to this directory
std::vector<TheButtonInfo> getInfoIn (std::string loc) {

    std::vector<TheButtonInfo> out =  std::vector<TheButtonInfo>();
    QDir dir(QString::fromStdString(loc) );
    QDirIterator it(dir);

    while (it.hasNext()) { // for all files

        QString f = it.next();
        std::cout<< f.toStdString() <<std::endl;

            if (f.contains("."))

#if defined(_WIN32)
            if (f.contains(".wmv"))  { // windows
#else
            if (f.contains(".mp4") || f.contains("MOV"))  { // mac/linux
#endif

            QString thumb = f.left( f .length() - 4) +".png";
            if (QFile(thumb).exists()) { // if a png thumbnail exists
                QImageReader *imageReader = new QImageReader(thumb);
                    QImage sprite = imageReader->read(); // read the thumbnail
                    if (!sprite.isNull()) {
                        QIcon* ico = new QIcon(QPixmap::fromImage(sprite)); // voodoo to create an icon for the button
                        QUrl* url = new QUrl(QUrl::fromLocalFile( f )); // convert the file location to a generic url
                        out.push_back(TheButtonInfo(url, ico)); // add to the output list
                    }
                    else
                        qDebug() << "warning: skipping video because I couldn't process thumbnail " << thumb << endl;
            }
            else
                qDebug() << "warning: skipping video because I couldn't find thumbnail " << thumb << endl;
        }
    }
    return out;
}

std::vector<TheButtonInfo> getInfo (std::string loc) {

    std::vector<TheButtonInfo> out =  std::vector<TheButtonInfo>();
    QDir dir(QString::fromStdString(loc) );
    QDirIterator it(dir);
    std::cout<< "f.toStdString()" <<std::endl;

    while (it.hasNext()) { // for all files

        QString f = it.next();
        if (f.contains(".png"))  {
        std::cout<< f.toStdString() <<std::endl;

        QString thumb = f.left( f .length() - 4) +".png";
        QImageReader *imageReader = new QImageReader(thumb);
        QImage sprite = imageReader->read(); // read the thumbnail
        QIcon* ico = new QIcon(QPixmap::fromImage(sprite)); // voodoo to create an icon for the button
        QUrl* url = new QUrl(QUrl::fromLocalFile(f)); // convert the file location to a generic url
        out . push_back(TheButtonInfo(url, ico)); // add to the output list
        }
    }

    return out;
}

int main(int argc, char *argv[]) {

    // let's just check that Qt is operational first
    qDebug() << "Qt version: " << QT_VERSION_STR << endl;

    // create the Qt Application
    QApplication app(argc, argv);
    // create the main window and layout
    QWidget window;
    QHBoxLayout *primeWindow = new QHBoxLayout();
    window.setLayout(primeWindow);

    PlayerWindow videoWindow;
    videoWindow.assemble(argc, argv);

    PlaylistsWindow playlistWindow;
    playlistWindow.hide();

    window.setWindowTitle("Tomeo");
    window.setMinimumSize(1000, 680);
    ControlButton* menu = new ControlButton(new QWidget());
    QHBoxLayout *menLay = new QHBoxLayout();
    //menu->setMaximumSize(30, 20);
    //menu->setMinimumSize(30, 20);
    menLay->setContentsMargins(0, 0, 0, 0);

    menLay->addWidget(menu);
    primeWindow->addLayout(menLay);


    SideBar * bar = new SideBar();
    bar->hide();
    bar->edit->hide();

    menu->connect(menu, SIGNAL(clicked()), bar, SLOT (showIt()));
    menu->connect(menu, SIGNAL(clicked()), menu, SLOT (disapear()));
    bar->quit->connect(bar->quit, SIGNAL(clicked()), menu, SLOT (showIt()));
    bar->quit->connect(bar->quit, SIGNAL(clicked()), bar, SLOT (disapear()));

    bar->playingNow->connect(bar->playingNow, SIGNAL(clicked()), &playlistWindow, SLOT (disapear()));
    bar->playingNow->connect(bar->playingNow, SIGNAL(clicked()), &videoWindow, SLOT (showIt()));
    bar->playingNow->connect(bar->playingNow, SIGNAL(clicked()), bar->quit, SLOT (showIt()));
    bar->playingNow->connect(bar->playingNow, SIGNAL(clicked()), bar->edit, SLOT (disapear()));

    bar->playlists->connect(bar->playlists, SIGNAL(clicked()), &playlistWindow, SLOT (showIt()));
    bar->playlists->connect(bar->playlists, SIGNAL(clicked()), &videoWindow, SLOT (disapear()));
    bar->playlists->connect(bar->playlists, SIGNAL(clicked()), bar->quit, SLOT (disapear()));
    bar->playlists->connect(bar->playlists, SIGNAL(clicked()), bar->edit, SLOT (showIt()));


    primeWindow->addWidget(bar);
    primeWindow->addWidget(&videoWindow);
    primeWindow->addWidget(&playlistWindow);

    // showtime!
    window.show();

    // wait for the app to terminate
    return app.exec();
}
