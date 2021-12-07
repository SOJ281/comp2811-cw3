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
    //setMuted(true);
    qreal rate = 2;
    setPlaybackRate(rate);
}

//haven't finished yet error: audio device not support changing rate
void ThePlayer::re_wind(){
    //setMuted(true);
    qreal rate = -2;
    setPlaybackRate(rate);
}

//stop button, back to beginning and stop
void ThePlayer::stop_player(){
    stop();
}

//reload button, restart the video
void ThePlayer::replay(){
    setPosition(0);
    starter = 0;
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

QString calcTime(qint64 time) {
    time = time /1000;
    qint64 minutes = time/60;
    qint64 hours = minutes/60;
    if (minutes > 0)
        time = time % minutes;
    if (hours > 0)
        minutes = minutes % hours;
    QString endTime = "";
    if (time < 10)
        endTime += "0";
    endTime += QString::number(time) + ":";

    if (minutes < 10)
        endTime += "0";
    endTime += QString::number(minutes) + ":";

    endTime += QString::number(hours);

    return endTime;
}

void DurLabel::setTimeStamp() {
    //quint64 pos;
    //setText(QString::number(position/1000, 'G', 2)+"/"+QString::number(duration/1000));
    //double posit = position;
    setText(calcTime(position)+"/"+calcTime(duration));
}
