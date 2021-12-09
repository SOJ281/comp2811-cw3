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

void TheButton::square() {
    setMaximumHeight(width());
}

void ControlButton::init(TheButtonInfo* i) {
    setIcon( *(i->icon) );
    info =  i;
    std::cout<<i->url->fileName().toStdString()<<std::endl;
}

//get icon for each control button
void ControlButton::addIcon(QString str) {
    setWhatsThis(str);
    if (!str.compare("sDown")){
        setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    }
    else if (!str.compare("play")){
        setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
    else if (!str.compare("fForward")){
        setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    }
    else if (!str.compare("save")){
        setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
    }
    else if (!str.compare("stop")){
        setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    }
    else if (!str.compare("reload")){
        setIcon(style()->standardIcon(QStyle::SP_BrowserReload));
    }
    else if (!str.compare("add")){
        setIcon(style()->standardIcon(QStyle::SP_ArrowUp));
    }
}


void ControlButton::multiple(TheButtonInfo* i) {
    //setIcon( *(i->icon) );
    second =  i;
    std::cout<<i->url->fileName().toStdString()<<std::endl;
}

void ControlButton::switching(QMediaPlayer::State state) {
    switch (state) {
      case QMediaPlayer::State::PausedState:
        setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        break;
      case QMediaPlayer::PlayingState:
        setIcon(style()->standardIcon(QStyle::SP_MediaPause));
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

