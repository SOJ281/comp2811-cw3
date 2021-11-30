//
// Created by twak on 11/11/2019.
//

#include "the_button.h"

#include <QtCore/QDir>

#include <iostream>

void TheButton::init(TheButtonInfo* i) {
    setIcon( *(i->icon) );
    info =  i;
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
    std::cout<<i->url->fileName().toStdString()<<std::endl;
}

void ControlButton::multiple(TheButtonInfo* i) {
    //setIcon( *(i->icon) );
    second =  i;
    std::cout<<i->url->fileName().toStdString()<<std::endl;
}

void ControlButton::switching(TheButtonInfo* i) {
    std::cout<<"attempting" <<std::endl;
    //setIcon( *(info->icon) );
    //init(info);
    //std::cout<<"success" <<std::endl;
    if(i->url->fileName().compare("play.png") || i->url->fileName().compare("pause.png")){
      //  init(info);
        setIcon( *(second->icon) );
        //TheButtonInfo temp = *info;
        //*info = *second;
        //*second = temp;
    }

}

void ControlButton::clicked() {
    //std::cout<<"attempting" <<std::endl;
    //setIcon( *(info->icon) );
    //init(info);
    //std::cout<<"success" <<std::endl;
    //if(info->url->fileName().compare("play.png") || info->url->fileName().compare("pause.png")){
      //  init(info);
        //setIcon( *(second->icon) );
        //TheButtonInfo temp = *info;
        //*info = *second;
        //*second = temp;
    //}

    emit jumpTo(info);
}

