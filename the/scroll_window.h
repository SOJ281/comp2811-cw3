//
// Created by twak on 14/10/2019.
//

#ifndef RESPONSIVEWINDOW_H
#define RESPONSIVEWINDOW_H

#include <QWidget>
#include "the_button.h"


//Window inside scroll area
class ScrollWindow: public QWidget {

public:
    ScrollWindow(std::vector<TheButton*>* buttons, int layout); //1 for QV, 2 for vector

protected:
    void createWidgets();
};


#endif //RESPONSIVEWINDOW_H
