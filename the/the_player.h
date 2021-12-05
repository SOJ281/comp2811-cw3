  //
// Created by twak on 11/11/2019.
//

#ifndef CW2_THE_PLAYER_H
#define CW2_THE_PLAYER_H


#include <QApplication>
#include <QMediaPlayer>
#include "the_button.h"
#include <vector>
#include <QTimer>

#include <QLabel>

class ThePlayer : public QMediaPlayer {

Q_OBJECT

private:
    std::vector<TheButtonInfo>* infos;
    std::vector<TheButton*>* buttons;
    QTimer* mTimer;
    long updateCount = 0;

public:
    ThePlayer() : QMediaPlayer(NULL) {
        setVolume(0); // be slightly less annoying
        connect (this, SIGNAL (stateChanged(QMediaPlayer::State)), this, SLOT (playStateChanged(QMediaPlayer::State)) );
    }
    int starter = 1;

    // all buttons have been setup, store pointers here
    void setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i);

private slots:

    // change the image and video for one button every one second
    void shuffle();

    void playStateChanged (QMediaPlayer::State ms);

    void pausePlay();

    void play_fast();

    void re_wind();

    void stop_player();

    void replay();

    void checkTime(qint64);

public slots:

    // start playing this ButtonInfo
    void jumpTo (TheButtonInfo* button);

//public signal:
    //durationChanged();

};

class DurLabel : public QLabel {
Q_OBJECT
public:
    qint64 position;
    qint64 duration;
    void setTimeStamp();

private slots:
    void setPos(qint64);
    void setDur(qint64);
};

#endif //CW2_THE_PLAYER_H
