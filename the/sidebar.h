#ifndef SIDEBAR_H
#define SIDEBAR_H

#include "iconlabelcontainer.h"
#include <QFrame>
#include <QObject>
class QHBoxLayout;

class SideBar : public QFrame {
  Q_OBJECT
public:
  explicit SideBar(QFrame *parent = nullptr);

private:
  void createWidgets();
  void arrangeWidgets();
  void makeConnections();
  QHBoxLayout *horizontal;
public:
  IconLabelContainer *playingNow =
      new IconLabelContainer("Playing now", ":/myplaylist/icons/icons/icons8-play-38.png");
  IconLabelContainer *videos =
      new IconLabelContainer("Videos", ":/myplaylist/icons/icons/icons8-video-38.png");
  IconLabelContainer *playlists =
      new IconLabelContainer("Playlists", ":/myplaylist/icons/icons/icons8-video-playlist-38.png");
  IconLabelContainer *edit = new IconLabelContainer(
      "Playlist edit", ":/myplaylist/icons/icons/icons8-video-playlist-edit-38.png");
  IconLabelContainer *quit =
      new IconLabelContainer("Quit", ":/myplaylist/icons/icons/icons8-close-38.png");

private slots:
  void disapear();
  void showIt();
};

#endif // SIDEBAR_H
