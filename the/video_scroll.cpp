//
// Created by twak on 14/10/2019.
//

#include <QFrame>
#include "video_scroll.h"

#include "scroll_window.h"
#include "scroll_layout.h"


//Constructors for ResponsiveScroll, same set up as label
//but puts name in different place and adds window
VideoScroll::VideoScroll(QString name, std::vector<TheButton*> *buttons, int layout) : VideoScroll(name, buttons, layout, "#9dceff") {}

VideoScroll::VideoScroll(QString name, std::vector<TheButton*> *buttons, int layout, QString colour) : QScrollArea() {
    setWhatsThis(name); //Used as identifier later
    setWidget(new class ScrollWindow(buttons, layout));
    setWidgetResizable(true);
    QColor qc (colour);
    qc = qc.darker(150);

    setStyleSheet("border: 1px solid "+ qc.name() +"; border-radius: 4px; background-color : "+
                  colour+"; color : black;");
    setAlignment(Qt::AlignCenter);
}
