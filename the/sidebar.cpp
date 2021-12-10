#include "sidebar.h"
#include "iconlabelcontainer.h"
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>

SideBar::SideBar(QFrame *parent) : QFrame(parent) {
  createWidgets();
  arrangeWidgets();
  makeConnections();
}

void SideBar::createWidgets() { horizontal = new QHBoxLayout(); }

void SideBar::arrangeWidgets() {
  // Divide window in left toolbar area and remaining area
  setStyleSheet("background-color: orange");
  horizontal = new QHBoxLayout(this);
  horizontal->setContentsMargins(0, 0, 0, 0);
  // horizontal->setSpacing(0);

  auto *leftToolBar = new QVBoxLayout();
  horizontal->addLayout(leftToolBar);
  QFrame *line = new QFrame;
  line->setFrameShape(QFrame::VLine);
  horizontal->addWidget(line);

  // Populate left toolbar

  // Note: stretch is used to make the items vertically centered
  leftToolBar->addStretch(1);
  leftToolBar->addWidget(playingNow);
  leftToolBar->addWidget(videos);
  leftToolBar->addWidget(playlists);
  leftToolBar->addWidget(edit);
  leftToolBar->addWidget(quit);
  leftToolBar->addStretch(1);
}

void SideBar::showIt() {
    show();
}

void SideBar::disapear() {
    hide();
}


// unused
void SideBar::makeConnections() {}
