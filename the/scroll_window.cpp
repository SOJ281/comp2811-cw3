//
// Created by twak on 14/10/2019.
//

#include "scroll_window.h"
#include "scroll_layout.h"
#include "the_button.h"
#include <QApplication>
#include <iostream>


//methods for scroll window
ScrollWindow::ScrollWindow(std::vector<TheButton*> * buttons) {

    setWindowTitle("2811 coursework 2: responsive layouts");
    setMinimumSize(0, 0);
    setMaximumSize(4000, 4000);

    ScrollLayout * rl = new ScrollLayout();
    //QWidget *buttonWidget = new QWidget();
    for(TheButton* i : *buttons) {
        std::cout << "Counting" << std::endl;
        i -> setWhatsThis("button");
        rl->addWidget(i);
       }
    setLayout(rl);

    //createWidgets();
}

void ScrollWindow::createWidgets() {

    ScrollLayout * rl = new ScrollLayout();
    QWidget *buttonWidget = new QWidget();
    for ( int i = 0; i < 4; i++ ) {
        TheButton *button = new TheButton(buttonWidget);
        button->setWhatsThis("button");
        //button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), player, SLOT (jumpTo(TheButtonInfo*))); // when clicked, tell the player to play.
        //buttons.push_back(button);
        rl->addWidget(button);
        //button->init(&videos.at(i));
    }
    setLayout(rl);
}
