//
// Created by twak on 11/11/2019.
//

#include "the_player.h"

#include <iostream>

// all buttons have been setup, store pointers here
void ThePlayer::setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i) {
  buttons = b;
  infos = i;
  jumpTo(buttons -> at(0) -> info);
}

// change the image and video for one button every one second
void ThePlayer::shuffle() {
  TheButtonInfo* i = & infos -> at (rand() % infos->size() );
  //        setMedia(*i->url);
  buttons -> at( updateCount++ % buttons->size() ) -> init( i );
}

void ThePlayer::playStateChanged (QMediaPlayer::State ms) {
  switch (ms) {
    case QMediaPlayer::State::StoppedState:
      play(); // starting playing again...
      break;
    default:
      break;
  }
}

void ThePlayer::jumpTo (TheButtonInfo* button) {
  setMedia( * button -> url);
  play();
}

//pauses/plays media player
void ThePlayer::pausePlay() {
    switch (state()) {
      case QMediaPlayer::State::PausedState:
        starter = 0;
        play(); // starting playing again...
        break;
      case QMediaPlayer::PlayingState:
        pause();
        break;
      default:
        break;
    }
}

//haven't finished yet error: audio device not support changing rate
void ThePlayer::play_fast(){
    setMuted(true);
    qreal rate = 2;
    setPlaybackRate(rate);
}

//haven't finished yet error: audio device not support changing rate
void ThePlayer::re_wind(){
    setMuted(true);
    qreal rate = -2;
    setPlaybackRate(rate);
}

//stop button, back to beginning and stop
void ThePlayer::stop_player(){
    stop();
    pause();
}

//reload button, restart the video
void ThePlayer::replay(){
    stop();
}

void ThePlayer::checkTime(qint64 time) {
    if (time <= 0 && starter > 1) {
        starter = 0;
        setPlaybackRate(1);
        pause();
    } else {
        if (starter < 2)
            starter++;
    }
}

void DurLabel::setPos(qint64 pos) {
    position = pos;
    setTimeStamp();
}
void DurLabel::setDur(qint64 dura) {
    duration = dura;
}
void DurLabel::setTimeStamp() {
    setText(QString::number(position/1000)+"/"+QString::number(duration/1000));
}
