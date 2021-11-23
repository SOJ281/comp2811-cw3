//
// Created by twak on 07/10/2019.
//

#ifndef RESPONSIVELAYOUT_H
#define RESPONSIVELAYOUT_H

#include <QtGui>
#include <QList>
#include <QLayout>
#include <QScrollArea>
#include "the_button.h"

//Layout for scroll window
class ScrollLayout : public QLayout {
public:
    //ResponsiveScrollLayout(std::vector<TheButton*> buttons);
    void setGeometry(const QRect &rect);
    void thin(const QRect &r);
    void wide(const QRect &r);
    void shiftSearch();

    void addItem(QLayoutItem *item);
    QSize sizeHint() const;
    QSize minimumSize() const;
    int count() const;
    QLayoutItem *itemAt(int) const;
    QLayoutItem *takeAt(int);

protected:
    QList<QLayoutItem*> list_;

};
#endif // RESPONSIVELAYOUT_H
