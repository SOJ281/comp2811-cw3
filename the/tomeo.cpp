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
#include "video_scroll.h"

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

void switchIcon(ControlButton * playing) {

}


int main(int argc, char *argv[]) {

    // let's just check that Qt is operational first
    qDebug() << "Qt version: " << QT_VERSION_STR << endl;

    // create the Qt Application
    QApplication app(argc, argv);

    // collect all the videos in the folder
    std::vector<TheButtonInfo> videos;

    if (argc == 2)
        videos = getInfoIn(std::string(argv[1])+"/videos");

    if (videos.size() == 0) {

        const int result = QMessageBox::question(
                    NULL,
                    QString("Tomeo"),
                    QString("no videos found! download, unzip, and add command line argument to \"quoted\" file location. Download videos from Tom's OneDrive?"),
                    QMessageBox::Yes |
                    QMessageBox::No );

        switch( result )
        {
        case QMessageBox::Yes:
          QDesktopServices::openUrl(QUrl("https://leeds365-my.sharepoint.com/:u:/g/personal/scstke_leeds_ac_uk/EcGntcL-K3JOiaZF4T_uaA4BHn6USbq2E55kF_BTfdpPag?e=n1qfuN"));
          break;
        default:
            break;
        }
        exit(-1);
    }

    // the widget that will show the video
    QVideoWidget *videoWidget = new QVideoWidget;

    // the QMediaPlayer which controls the playback
    ThePlayer *player = new ThePlayer;
    player->setVideoOutput(videoWidget);

    // a row of buttons
    QWidget *buttonWidget = new QWidget();
    // a list of the buttons
    std::vector<TheButton*> buttons;
    // the buttons are arranged horizontally
    QVBoxLayout *right = new QVBoxLayout();
    buttonWidget->setLayout(right);


    //control buttons panel
    std::vector<TheButtonInfo> control = getInfo(std::string(argv[1])+"/buttons"); //array of buttons
    //Array of buttons, order here determines order of buttons
    std::vector<QString> buttonTypes = {"sDown.png", "pause.png", "fForward.png", "save.png", "stop.png", "reload.png", "add.png"};
    QHBoxLayout *leftBottom = new QHBoxLayout();

    for(QString i : buttonTypes) { //Loops through buttons types
        for(TheButtonInfo bc : control) { //loops through button info
            if(!(bc.url->fileName().compare(i))) { //if both same buttontype
                ControlButton *funcButton = new ControlButton(buttonWidget);
                funcButton->setMinimumSize(70, 70);
                funcButton->setMaximumSize(70, 70);
                leftBottom->addWidget(funcButton);
                funcButton->init(&bc);
                funcButton->setIconSize(QSize(70, 70));
                if (!(bc.url->fileName().compare("pause.png"))) {
                    for(TheButtonInfo sc : control) {
                        if (!(sc.url->fileName().compare("play.png"))) {
                            funcButton->multiple(&sc);
                            //funcButton->init(&sc);
                            //std::cout<<"multiple buttons";
                        }
                    }
                    //funcButton->connect(funcButton, SIGNAL(jumpTo(TheButtonInfo*)), funcButton, SLOT(switching(TheButtonInfo*)));
                    funcButton->connect(funcButton, SIGNAL(clicked()), player, SLOT(pausePlay())); // when clicked, tell the player to play.
                } else if (!(bc.url->fileName().compare("add.png"))) {
                    std::cout<<"ikborshnuiedbhureigbudif"<<std::endl;
                    QWidget *dialogueBox = new QWidget;
                    QHBoxLayout *lay = new QHBoxLayout();
                    //ControlButton *bee = new ControlButton(buttonWidget);
                    QLabel* title = new QLabel("Title:");
                    title->setMinimumSize(70, 30);
                    title->setMaximumSize(70, 30);
                    lay->addWidget(title);
                    QLineEdit *reader = new QLineEdit();
                    reader->setMinimumSize(170, 30);
                    reader->setMaximumSize(170, 30);
                    lay->addWidget(reader);

                    QPushButton *bee = new QPushButton("Add");
                    bee->setMinimumSize(70, 30);
                    bee->setMaximumSize(70, 30);
                    //lay->addWidget(bee);
                    QVBoxLayout *backLayout = new QVBoxLayout();
                    backLayout->addLayout(lay);

                    QVBoxLayout *lowerLay = new QVBoxLayout();
                    //lowerLay->addWidget(bee);
                    for (TheButtonInfo ac : control) {
                        if(!(ac.url->fileName().compare("dragDrop.png"))) {
                            ControlButton *downButton = new ControlButton(buttonWidget);
                            downButton->setMinimumSize(400, 100);
                            downButton->setMaximumSize(400, 100);
                            downButton->init(&ac);
                            downButton->setIconSize(QSize(400, 100));
                            lowerLay->addWidget(downButton);
                        }
                    }
                    lowerLay->addWidget(bee);
                    backLayout->addLayout(lowerLay);


                    dialogueBox->setLayout(backLayout);
                    dialogueBox->setWindowTitle("tomeo");
                    dialogueBox->setMinimumSize(400, 450);
                    dialogueBox->show();
                    dialogueBox->hide();

                    funcButton->connect(funcButton, SIGNAL(clicked()), dialogueBox, SLOT(show())); // when clicked, tell the player to play.
                }
            }
        }
    }
    QSpacerItem *space = new QSpacerItem(70,70, QSizePolicy::MinimumExpanding);
    leftBottom->addItem(space);

    QVBoxLayout *left = new QVBoxLayout();
    left->addWidget(videoWidget);
    left->addLayout(leftBottom);
    left->setSpacing(10);

    // create the 7 video buttons
    for ( int i = 0; i < 6; i++) {
        TheButton *button = new TheButton(buttonWidget);
        button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), player, SLOT (jumpTo(TheButtonInfo*))); // when clicked, tell the player to play.
        buttons.push_back(button);
        button->setMaximumWidth(250);
        //right->addWidget(button);
        button->init(&videos.at(i));
    }

    VideoScroll *rightScroll = new VideoScroll(QString("scroll"), &buttons, 1); //passess scroll bar data
    rightScroll->setMinimumWidth(250);
    rightScroll->setMaximumWidth(250);
    rightScroll->setMinimumHeight(680);
    right->addWidget(rightScroll);
    //right->addStretch(1);
    right->minimumSize();

    // tell the player what buttons and videos are available
    player->setContent(&buttons, & videos);

    // create the main window and layout
    QWidget window;
    QHBoxLayout *top = new QHBoxLayout();
    window.setLayout(top);
    window.setWindowTitle("tomeo");
    window.setMinimumSize(800, 680);

    // add the video and the buttons to the top level widget
    top->addLayout(left);
    top->addWidget(buttonWidget);
    top->addStretch(1);
    //setModal(false);

    // showtime!
    window.show();

    // wait for the app to terminate
    return app.exec();
}
