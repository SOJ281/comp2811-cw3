#include "scrollgridlayout.h"
#include "constants.h"
#include <QFrame>
#include <iostream>

void ScrollGridLayout::setGeometry(const QRect &r) {

  QLayout::setGeometry(r);

  if (list_.size() == 0)
    return;

  // calculate the widget size
  int columns = widgetSpace(r.width());
  int columnSize = r.width() / columns;

  int topPos = r.top(), leftPos = r.left();

  for (int i = 0; i < list_.length(); ++i) {
    QWidget *wid = list_[i]->widget();

    // if no space on the line is left, go to the next line
    if (leftPos + columnSize > (r.left() + r.width())) {
      leftPos = 0;
      topPos += kPlaylistHeight;
    }

    wid->setGeometry(leftPos, topPos, columnSize, kPlaylistHeight);
    leftPos += columnSize;
  }
}

// function to calculate widget based on window size and space available
int ScrollGridLayout::widgetSpace(int width) const {
  for (int i = 20; i > 0; i--)
    if (width / i > kMinimumPlaylistWidth)
      return i;
  return 1;
}

int ScrollGridLayout::count() const { return list_.size(); }

QLayoutItem *ScrollGridLayout::itemAt(int idx) const { return list_.value(idx); }

QLayoutItem *ScrollGridLayout::takeAt(int idx) {

  return idx >= 0 && idx < list_.size() ? list_.takeAt(idx) : 0;
}

void ScrollGridLayout::addItem(QLayoutItem *item) { list_.append(item); }

QSize ScrollGridLayout::sizeHint() const {

  // get width of the scrollArea (not the scrollViewport)
  int width = parentWidget()->parentWidget()->width();

  if (width == 0)
    return QSize(0, 0);

  // if the viewport is below the minimum treat is as if it wasn't
  else if (width < kMinimumViewportSize)
    width = kMinimumViewportSize;

  int columns = widgetSpace(width);

  // formula to do ceil rounding with integers: (a + b-1) / b = ceil(a/b)
  int height = (count() + columns - 1) / columns * kPlaylistHeight;

  QSize size(width, height);

  return size;
}

QSize ScrollGridLayout::minimumSize() const { return sizeHint(); }

ScrollGridLayout::~ScrollGridLayout() {

  QLayoutItem *item;
  while ((item = takeAt(0)))
    delete item;
}
