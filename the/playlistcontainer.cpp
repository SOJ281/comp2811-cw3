#include "playlistcontainer.h"
#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>

PlaylistContainer::PlaylistContainer(QString playlistName, int videosCount, QString imagePath,
                                     QFrame *parent) {
  setStyleSheet(".QFrame{border: 1px solid black; border-radius: 5px; margin-bottom: 5px; "
                "margin-right: 5px;}");
  // this->setFrameStyle(QFrame::Panel);
  // Main container
  container = new QVBoxLayout(this);

  check = new QCheckBox();
  auto *header = new QHBoxLayout();
  header->addStretch();
  header->addWidget(check);
  container->addLayout(header);

  // Load image for thumbnail
  QPixmap image;

  if (imagePath != "")
    image.load(imagePath);
  else
    // If no image is provided, load default
    image.load(":/myplaylist/icons/icons/icons8-video-playlist-100.png");

  thumbnail = new QLabel();
  thumbnail->setPixmap(image);
  container->addWidget(thumbnail);
  container->setAlignment(thumbnail, Qt::AlignCenter);

  playbutton = new QPushButton();
  playbutton->setCursor(Qt::PointingHandCursor);
  playbutton->setStyleSheet("border: none");

  QPixmap playIcon(":/myplaylist/icons/icons/icons8-play-48.png");
  playbutton->setIcon(playIcon);
  playbutton->setIconSize(playIcon.rect().size());

  name = new QLabel(playlistName);
  counter = new QLabel(QString::number(videosCount) + " items");
  vidNumber = videosCount;

  // Arrange the layout of the container
  auto *bottom = new QHBoxLayout();
  auto *bottomLeft = new QVBoxLayout();

  container->addLayout(bottom);

  bottomLeft->addStretch();
  bottomLeft->addWidget(name);
  bottomLeft->addWidget(counter);
  bottomLeft->addStretch();

  bottom->addLayout(bottomLeft);
  bottom->addStretch();

  bottom->addWidget(playbutton);
}
