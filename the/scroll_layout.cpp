//
// Created by twak on 07/10/2019.
//

#include "scroll_layout.h"
#include "video_scroll.h"
#include <iostream>
#include "the_button.h"


//Below methods for scrollLayout class

//Runs when scroll panel is resized
void ScrollLayout::setGeometry(const QRect &r) { // our layout should fit inside r
    QLayout::setGeometry(r);
    thin(r);

    //Determines width

    //if (r.width() < 700) {
    //    thin(r);
    //} else {
       // wide(r);
    //}
}
void ScrollLayout::thin(const QRect &r) {
    QLayout::setGeometry(r);
/*
    int count = 0; //Counts search results placed
    int rowLength = 2; //Number of results per row
    int div = 3; //Determines size of result
    int margin = r.width()*.03;
    //int searchB;
    if (r.width() > 600) {
        rowLength = 3;
        div = 5;
    }
    double rISize[2] = {(double)(r.width())/div, (double)(r.width()/div *.8)};
    double rTSize[2] = {(double)(r.width())/div, (double)(r.width()/div *.2)};
    int buffer = (r.width() - (rISize[0])*rowLength - (margin)*(rowLength-1))/2;*/

    int count = 0, margin = r.width()*.015, buffer;// = r.width()/10;
    //double rISize[2] = {(double)(r.width())/6, (double)(r.width()/6 *.8)};
    double rISize[2] = {(double)(r.width())/6, (double)(r.width()/6 *.8)};
    double rTSize[2] = {(double)(r.width())/6, (double)(r.width()/6 *.2)};
    int rowLength = 2; //Number of results per row
    buffer = 10;
    if (r.width() > 1000) {
        rowLength = 5;
        rISize[0] = rISize[0]*.9;
        rISize[1] = rISize[1]*.9;
        rTSize[0] = rTSize[0]*.9;
        rTSize[1] = rTSize[1]*.9;
    }

    for (int i = 0; i < list_.size(); i++) {
        QLayoutItem *o = list_.at(i);
        try {
            TheButton *button = static_cast<TheButton *>(o->widget());
            if (button == NULL) // null: cast failed on pointer
                std::cout << "warning, unknown widget class in layout" << std::endl;
            else if (button -> whatsThis() == "button" ) {
                //button -> setHeight(rISize[1]);
                //button -> setMaximumSize(rISize[1]);
                //button -> setGeometry(buffer + (button->width() +margin)*floor(count%rowLength),
                    //100 + (button->height()+rTSize[1]+margin)*floor(count/rowLength),
                    //button->width(), button->height());
                button -> setGeometry(buffer + (button->width()+margin)*floor(count%rowLength),
                    buffer + (button->height()+rTSize[1]+margin)*floor(count/rowLength),
                    button->width(), button->height());
                count++;
            }
        } catch (std::bad_cast) {
            // bad_case: cast failed on reference...
            std::cout << "warning, unknown widget class in layout" << std::endl;
        }
    }
    //Sets depth of scroll to fit all results
    //int depth = 220+(rISize[1]+rTSize[1]+margin)*floor(count/rowLength)+rISize[1];
    //parentWidget()->setMinimumHeight(depth);
}

/*
//Runs for small width
void ResponsiveScrollLayout::thin(const QRect &r) {
    QLayout::setGeometry(r);

    int count = 0; //Counts search results placed
    int rowLength = 2; //Number of results per row
    int div = 3; //Determines size of result
    int margin = r.width()*.03;
    int searchB;
    if (r.width() > 600) {
        rowLength = 3;
        div = 5;
    }
    double rISize[2] = {(double)(r.width())/div, (double)(r.width()/div *.8)};
    double rTSize[2] = {(double)(r.width())/div, (double)(r.width()/div *.2)};
    int buffer = (r.width() - (rISize[0])*rowLength - (margin)*(rowLength-1))/2;

    for (int i = 0; i < list_.size(); i++) {
        QLayoutItem *o = list_.at(i);
        try {
            ResponsiveLabel *label = static_cast<ResponsiveLabel *>(o->widget());
            if (label == NULL) // null: cast failed on pointer
                std::cout << "warning, unknown widget class in layout" << std::endl;
            else if (label -> text() == kSResultImage )
                label -> setGeometry(buffer  + (rISize[0] +margin)*floor(count%rowLength),
                    100 + (rISize[1]+rTSize[1]+margin)*floor(count/rowLength),
                    rISize[0], rISize[1]);
            else if (label -> text() == kSResultText ) {
                label -> setGeometry(buffer + (rISize[0] + margin)*floor(count%rowLength),
                    100+(rISize[1]+rTSize[1]+margin)*floor(count/rowLength)+rISize[1],
                    rTSize[0], rTSize[1]);
                count++;
            } else if (label -> text() == kSBackward ) {
                searchB = 120+(rISize[1]+rTSize[1]+margin)*floor(count/rowLength)+rISize[1] + 40;
                label -> setGeometry((r.width()-90)/2, searchB, 20, 20);
            } else if (label -> text() == kSPageNo )
                label -> setGeometry((r.width())/2 - 10, searchB, 20, 20);
            else if (label -> text() == kSForward )
                label -> setGeometry((r.width()-90)/2 + 70, searchB, 20, 20);
        }
        catch (std::bad_cast) {
            // bad_case: cast failed on reference...
            std::cout << "warning, unknown widget class in layout" << std::endl;
        }
    }
    //Sets depth of scroll to fit all results
    int depth = 220+(rISize[1]+rTSize[1]+margin)*floor(count/rowLength)+rISize[1];
    parentWidget()->setMinimumHeight(depth);
}

void ResponsiveScrollLayout::wide(const QRect &r) {
    int count = 0, margin = r.width()*.015, buffer = r.width()/10, searchB;
    double rISize[2] = {(double)(r.width())/6, (double)(r.width()/6 *.8)};
    double rTSize[2] = {(double)(r.width())/6, (double)(r.width()/6 *.2)};
    if (r.width() > 1000) {
        shiftSearch();
        rISize[0] = rISize[0]*.9;
        rISize[1] = rISize[1]*.9;
        rTSize[0] = rTSize[0]*.9;
        rTSize[1] = rTSize[1]*.9;
        buffer = r.width()/4;
    }
    //Width of search results space
    int searchW = r.width()/4 + (rISize[0]+margin)*4;
    for (int i = 0; i < list_.size(); i++) {
        QLayoutItem *o = list_.at(i);
        try {
            ResponsiveLabel *label = static_cast<ResponsiveLabel *>(o->widget());
            if (label == NULL) // null: cast failed on pointer
                std::cout << "warning, unknown widget class in layout" << std::endl;
            else if (label -> text() == kSResultImage)
                label -> setGeometry(buffer + (rISize[0]+margin)*floor(count%4),
                    100 + (rISize[1]+rTSize[1] +margin)*floor(count/4),
                    rISize[0], rISize[1]);
            else if (label -> text() == kSResultText) {
                label -> setGeometry(buffer + (rISize[0]+margin)*floor(count%4),
                    100 + (rISize[1]+rTSize[1]+margin)*floor(count/4) + rISize[1],
                    rTSize[0], rTSize[1]);
                count++;
            } else if (label -> text() == kAdvert)
                label -> setGeometry(r.width() - 100, 70, 80, r.height() - 150);
            else if (label -> text() == kSBackward ) {
                searchB = 160+(rISize[1]+rTSize[1]+margin)*floor(count/4)+rISize[1];
                label -> setGeometry(searchW - 120, searchB, 30, 30);
            } else if (label -> text() == kSPageNo)
                label -> setGeometry(searchW - 80, searchB, 40, 30);
            else if (label -> text() == kSForward)
                label -> setGeometry(searchW - 30, searchB, 30, 30);
        } catch (std::bad_cast) {
            std::cout << "warning, unknown widget class in layout" << std::endl;
        }
    }
    //Sets depth of scroll to fit all results
    int depth = 250 + (rISize[1]+rTSize[1]+margin)*floor(count/4) + rISize[1];
    parentWidget()->setMinimumHeight(depth);
}

/*
//Moves search to left and puts full sized filter
void ResponsiveScrollLayout::shiftSearch() {
    for (int i = 0; i < list_.size(); i++) {
        QLayoutItem *o = list_.at(i);
        try {
            ResponsiveLabel *label = static_cast<ResponsiveLabel *>(o->widget());
            if (label == NULL) // null: cast failed on pointer
                std::cout << "warning, unknown widget class in layout" << std::endl;
            else if (label -> text() == kSQuery)
                label -> setGeometry(10, 80, 100, 30);
            else if (label -> text() == kSOptions)
                label -> setGeometry(115, 80, 60, 30);
            else if (label -> text() == kSButton)
                label -> setGeometry(180, 80, 60, 30);
            else if (label -> text() == kSFilterBox)
                label -> setGeometry(10, 120, 220, 400);
         } catch (std::bad_cast) {
                std::cout << "warning, unknown widget class in layout" << std::endl;
         }
    }
}
*/
// following methods provide a trivial list-based implementation of the QLayout class
int ScrollLayout::count() const {

    return list_.size();
}

QLayoutItem *ScrollLayout::itemAt(int idx) const {

    return list_.value(idx);
}

QLayoutItem *ScrollLayout::takeAt(int idx) {

    return idx >= 0 && idx < list_.size() ? list_.takeAt(idx) : 0;
}

void ScrollLayout::addItem(QLayoutItem *item) {

    list_.append(item);
}

QSize ScrollLayout::sizeHint() const {

    return minimumSize();
}

QSize ScrollLayout::minimumSize() const {

    return QSize(320,320);
}
/*
ScrollLayout::~ScrollLayout() {

    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}*/
