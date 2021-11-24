//
// Created by twak on 11/11/2019.
//

#include "the_button.h"

#include <QtCore/QDir>

void TheButton::init(TheButtonInfo* i) {
    setIcon( *(i->icon) );
    info =  i;
    //setText(i->url->fileName());
    setText(i->url->fileName().left(i->url->fileName().size()-4));
}


void TheButton::clicked() {
    emit jumpTo(info);
}
/*
void TheButton::pausePlay() {
    switch (info->url->fileName()) {
      case QMediaPlayer::State::PausedState:
        play(); // starting playing again...
        break;
      case QMediaPlayer::PlayingState:
        pause();
        break;
      default:
        break;
    }
}
*/

void ControlButton::init(TheButtonInfo* i) {
    setIcon( *(i->icon) );
    info =  i;
}
/*
void ControlButton::clicked() {
    QDir lsDir(info->url->path());
    if(info->url->fileName().compare("play.png")){

    }

    emit jumpTo(info);
}
*/
