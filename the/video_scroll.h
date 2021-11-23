//
// Created by twak on 14/10/2019.
//

#ifndef RESPONSIVELABEL_H
#define RESPONSIVELABEL_H


#include <QLabel>
#include <QString>
#include <map>
#include <QScrollArea>
#include "the_button.h"


//QScroll class
class VideoScroll: public QScrollArea {

public:
    VideoScroll(QString name, std::vector<TheButton*> *buttons);
    VideoScroll(QString name, std::vector<TheButton*> *buttons, QString colour);
};


#endif // RESPONSIVELABEL_H
