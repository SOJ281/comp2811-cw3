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

    //control buttons panel
    std::vector<TheButtonInfo> control = getInfo(std::string(argv[1])+"/button353"); //array of buttons

    //Array of buttons, order here determines order of buttons
    std::vector<QString> buttonTypes = {"sDown", "play", "fForward", "save", "stop", "reload", "add"};
    QHBoxLayout *leftBottom = new QHBoxLayout();
    QHBoxLayout *leftBottomL = new QHBoxLayout();

    for(QString i : buttonTypes){
        //adding new control buttons
        ControlButton *button = new ControlButton(buttonWidget);
        leftBottomL->addWidget(button);
        button->setMaximumSize(45, 45);
        button->setMinimumSize(45, 45);
        button->addIcon(i);

        //functionalities for each button
        if (!(i.compare("play"))) {
          button->connect(button, SIGNAL(clicked()), player, SLOT(pausePlay()));
          button->connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), button, SLOT(switching(QMediaPlayer::State)));
        }else if (!(i.compare("fForward"))) {
          button->connect(button, SIGNAL(clicked()), player, SLOT(play_fast()));
        }else if (!(i.compare("sDown"))) {
            button->connect(button, SIGNAL(clicked()), player, SLOT(re_wind()));
        }else if (!(i.compare("stop"))) {
          button->connect(button, SIGNAL(clicked()), player, SLOT(stop_player()));
        }else if (!(i.compare("reload"))) {
          button->connect(button, SIGNAL(clicked()), player, SLOT(replay()));
        }else if (!(i.compare("save"))){
          button->setIconSize(QSize(30, 30));
          QWidget *dialogueBox = new QWidget;
          QVBoxLayout *lay = new QVBoxLayout();
          QHBoxLayout *lay1 = new QHBoxLayout();
          lay->addLayout(lay1);
          QHBoxLayout *lay2 = new QHBoxLayout();
          lay->addLayout(lay2);

          QLabel* title1 = new QLabel("Save in folder:");
          //QFont font("Calibri Light", 14);
          //title1->setFont(font);
          lay1->addWidget(title1);
          QLineEdit *reader1 = new QLineEdit();
          reader1->setMinimumSize(200, 30);
          lay1->addWidget(reader1);

          QLabel* title2 = new QLabel("File name:");
          //title2->setFont(font);
          lay2->addWidget(title2);
          QLineEdit *reader2 = new QLineEdit();
          reader2->setMinimumSize(200, 30);
          lay2->addWidget(reader2);

          QPushButton *but = new QPushButton("Save");
          but->setMinimumSize(70, 30);
          but->setMaximumSize(70, 30);
          lay->addWidget(but);

          dialogueBox->setLayout(lay);
          dialogueBox->setWindowTitle("Save");
          dialogueBox->setMinimumSize(400, 170);

          QWidget *prompt = new QWidget();
          QHBoxLayout *promptLay = new QHBoxLayout();
          QLabel *message = new QLabel("Video saved successfully");
          promptLay->addWidget(message);
          prompt->setLayout(promptLay);
          prompt->setWindowTitle("Save");
          prompt->setMinimumSize(400, 100);

          but->connect(but, SIGNAL(clicked()), dialogueBox, SLOT(hide()));
          but->connect(but, SIGNAL(clicked()), prompt, SLOT(show())); // show prompt when clicked
          button->connect(button, SIGNAL(clicked()), dialogueBox, SLOT(show())); // when clicked, tell the player to play.
        }else if (!(i.compare("add"))) {
          button->setIconSize(QSize(40, 40));
          QWidget *dialogueBox = new QWidget;
          QHBoxLayout *lay = new QHBoxLayout();
          QLabel* title = new QLabel("Title:");
          //QFont font("Calibri Light", 16);
          //title->setFont(font);
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
          for (TheButtonInfo ac : getInfo(std::string(argv[1])+"/buttons")) {
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
          dialogueBox->setWindowTitle("Add a new video");
          dialogueBox->setMinimumSize(400, 250);
          dialogueBox->show();
          dialogueBox->hide();

          QWidget *prompt = new QWidget();
          QHBoxLayout *promptLay = new QHBoxLayout();
          QLabel *message = new QLabel("Video added successfully");
          promptLay->addWidget(message);
          prompt->setLayout(promptLay);
          prompt->setWindowTitle("Add a new video");
          prompt->setMinimumSize(400, 100);

          bee->connect(bee, SIGNAL(clicked()), dialogueBox, SLOT(hide()));
          bee->connect(bee, SIGNAL(clicked()), prompt, SLOT(show()));
          button->connect(button, SIGNAL(clicked()), dialogueBox, SLOT(show())); // when clicked, tell the player to play.
        }
    }

    QHBoxLayout *leftBottomR = new QHBoxLayout();
    //audio control
    QSlider* slider = new QSlider(Qt::Horizontal);
    slider->setRange(1, 100);
    slider->setMaximumWidth(100);
    slider->setMinimumWidth(80);
    slider->setTickPosition(QSlider::TicksBothSides);
    leftBottomR->addWidget(slider);
    leftBottomR->setAlignment(slider, Qt::AlignRight);
    player->connect(slider, SIGNAL(valueChanged(int)), player, SLOT(setVolume(int)));

    //label shows time
    DurLabel * duration = new DurLabel();
    duration->setText(QString::number(player->duration()));
    duration->setMaximumHeight(60);
    duration->setMinimumSize(60,60);

    leftBottomR->addWidget(duration);
    leftBottomR->setAlignment(duration, Qt::AlignRight);
    player->connect(player, SIGNAL(durationChanged(qint64)), duration, SLOT (setDur(qint64)));
    player->connect(player, SIGNAL(positionChanged(qint64)), duration, SLOT (setPos(qint64)));
    player->connect(player, SIGNAL(positionChanged(qint64)), player, SLOT (checkTime(qint64)));
    player->connect(player, SIGNAL(clicked()), player, SLOT (pausePlay()));

    leftBottom->addLayout(leftBottomL);
    leftBottom->addLayout(leftBottomR);

    QSpacerItem *space = new QSpacerItem(5,45, QSizePolicy::MinimumExpanding);
    leftBottomL->addItem(space);

    QVBoxLayout *left = new QVBoxLayout();
    left->addWidget(videoWidget);
    left->addLayout(leftBottom);
    leftBottom->setSpacing(5);

    // create the 7 video buttons
    for ( int i = 0; i < 7; i++) {
        TheButton *button = new TheButton(buttonWidget);
        button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), player, SLOT (jumpTo(TheButtonInfo*))); // when clicked, tell the player to play.
        //player->connect(button, SIGNAL(clicked()), duration, SLOT (setText("nudfsgi"))); // when clicked, tell the player to play.
        buttons.push_back(button);
        button->setMaximumWidth(250);
        button->init(&videos.at(i));
    }

    VideoScroll *rightScroll = new VideoScroll(QString("scroll"), &buttons, 1); //passess scroll bar data
    rightScroll->setMinimumSize(258, 620);
    rightScroll->setMaximumWidth(258);

    // tell the player what buttons and videos are available
    player->setContent(&buttons, & videos);

    // create the main window and layout
    QWidget window;
    QHBoxLayout *top = new QHBoxLayout();
    window.setLayout(top);
    window.setWindowTitle("Tomeo");
    window.setMinimumSize(800, 680);

    // add the video and the buttons to the top level widget
    top->addLayout(left);
    top->addWidget(rightScroll);

    // showtime!
    window.show();

    // wait for the app to terminate
    return app.exec();
}
