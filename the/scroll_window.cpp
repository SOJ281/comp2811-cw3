//
// Created by twak on 14/10/2019.
//

#include "scroll_window.h"
#include "the_button.h"
#include <QApplication>
#include <iostream>

#include <QtWidgets/QVBoxLayout>


//methods for scroll window
ScrollWindow::ScrollWindow(std::vector<TheButton*> * buttons, int layout) {

    setWindowTitle("2811 coursework 2: responsive layouts");
    setMinimumSize(0, 0);
    setMaximumSize(4000, 4000);

    if (layout == 1) {
        QVBoxLayout * rl = new QVBoxLayout();
        QSpacerItem *space = new QSpacerItem(0,0, QSizePolicy::MinimumExpanding);
        rl->addItem(space);
        //rl->setAlignment (alignment )
        for(TheButton* i : *buttons) {
            i -> setWhatsThis("button");
            rl->addWidget(i);
           }
        rl->addStretch();
        setLayout(rl);
     }
}
