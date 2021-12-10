//
// Created by twak on 11/11/2019.
//

#include "the_button.h"

#include <QtCore/QDir>
#include <QStyle>
#include <iostream>

void TheButton::init(TheButtonInfo* i) {
    setIcon( *(i->icon) );
    info =  i;
    setText(i->url->fileName().left(i->url->fileName().size()-4));
}


void TheButton::clicked() {
    emit jumpTo(info);
}

void ControlButton::init(TheButtonInfo* i) {
    setIcon( *(i->icon) );
    info =  i;
    std::cout<<i->url->fileName().toStdString()<<std::endl;
}

//get icon for each control button
void ControlButton::addIcon(QString str) {
  setWhatsThis(str);
  // playbutton->setIcon(playIcon);
  // playbutton->setIconSize(playIcon.rect().size());
  QPixmap myIcon;
  if (!str.compare("sDown")) {
    myIcon.load(":/myplaylist/icons/icons/icons8-rewind-38.png");
  } else if (!str.compare("play")) {
    myIcon.load(":/myplaylist/icons/icons/icons8-play-38.png");
  } else if (!str.compare("fForward")) {
    myIcon.load(":/myplaylist/icons/icons/icons8-fast-forward-38.png");
  } else if (!str.compare("save")) {
    myIcon.load(":/myplaylist/icons/icons/icons8-save-38.png");
  } else if (!str.compare("stop")) {
    myIcon.load(":/myplaylist/icons/icons/icons8-stop-38.png");
  } else if (!str.compare("reload")) {
    myIcon.load(":/myplaylist/icons/icons/icons8-refresh-38.png");
  } else if (!str.compare("add")) {
    myIcon.load(":/myplaylist/icons/icons/icons8-upload-38.png");
  }
  setIcon(myIcon);
  setIconSize(myIcon.rect().size());
}

void ControlButton::switching(QMediaPlayer::State state) {
  QPixmap pauseIcon(":/myplaylist/icons/icons/icons8-pause-38.png");
  QPixmap playIcon(":/myplaylist/icons/icons/icons8-play-38.png");
  switch (state) {

  case QMediaPlayer::State::PausedState:
    setIcon(playIcon);
    setIconSize(playIcon.rect().size());
    break;
  case QMediaPlayer::PlayingState:
    setIcon(pauseIcon);
    setIconSize(pauseIcon.rect().size());
    break;
  default:
    break;
  }
}

void ControlButton::clicked() {
    emit jumpTo(info);
}

void ControlButton::disapear() {
    hide();
}
void ControlButton::showIt() {
    show();
}

