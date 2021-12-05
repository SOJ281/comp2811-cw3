//
// Created by twak on 11/11/2019.
//

#ifndef CW2_THE_BUTTON_H
#define CW2_THE_BUTTON_H

#include <QPushButton>
#include <QUrl>

class TheButtonInfo {

public:
    QUrl* url; // video file to play
    QIcon* icon; // icon to display

    TheButtonInfo ( QUrl* url, QIcon* icon) : url (url), icon (icon) {}
};

class TheButton : public QPushButton {
    Q_OBJECT

public:
    TheButtonInfo* info;

     TheButton(QWidget *parent) :  QPushButton(parent) {
         setIconSize(QSize(200,110));
         connect(this, SIGNAL(released()), this, SLOT (clicked())); // if QPushButton clicked...then run clicked() below
    }

    void init(TheButtonInfo* i);


private slots:
    void clicked();
    //void pausePlay();

signals:
    void jumpTo(TheButtonInfo*);

};


//Class contains all control buttons (pause play etc)
class ControlButton : public TheButton {
    Q_OBJECT
public:
    TheButtonInfo* second;

    void init(TheButtonInfo* i);
    void addIcon(QString str);
    void multiple(TheButtonInfo* i);
    ControlButton(QWidget *parent) :  TheButton(parent) {
        setIconSize(QSize(80,80));
        connect(this, SIGNAL(released()), this, SLOT (clicked()));
   }

private slots:
    void clicked();
    void switching();

signals:
};


#endif //CW2_THE_BUTTON_H
