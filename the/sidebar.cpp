#include "sidebar.h"
#include "iconlabelcontainer.h"
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>

SideBar::SideBar(QWidget *parent) : QWidget(parent) {
  createWidgets();
  arrangeWidgets();
  makeConnections();
}

void SideBar::createWidgets() { horizontal = new QHBoxLayout(); }

void SideBar::arrangeWidgets() {
  // Divide window in left toolbar area and remaining area
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
  leftToolBar->addWidget(
      new IconLabelContainer("Playing now", ":/myplaylist/icons/icons/icons8-circled-play-24.png"));
  leftToolBar->addWidget(
      new IconLabelContainer("Videos", ":/myplaylist/icons/icons/icons8-laptop-play-video-24.png"));
  leftToolBar->addWidget(
      new IconLabelContainer("Playlists", ":/myplaylist/icons/icons/icons8-playlist-24.png"));
  leftToolBar->addWidget(new IconLabelContainer(
      "Playlist edit", ":/myplaylist/icons/icons/icons8-playlistedit-24.png"));
  leftToolBar->addWidget(
      new IconLabelContainer("Quit", ":/myplaylist/icons/icons/icons8-close-24.png"));
  leftToolBar->addStretch(1);
}

// unused
void SideBar::makeConnections() {}
