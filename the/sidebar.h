#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QObject>
#include "iconlabelcontainer.h"
class QHBoxLayout;

class SideBar : public QWidget {
    Q_OBJECT
public:
  explicit SideBar(QWidget *parent = nullptr);

private:
  void createWidgets();
  void arrangeWidgets();
  void makeConnections();
  QHBoxLayout *horizontal;
public:
  IconLabelContainer* playingNow = new IconLabelContainer("Playing now", ":/myplaylist/icons/icons/icons8-circled-play-24.png");
  IconLabelContainer* videos = new IconLabelContainer("Videos", ":/myplaylist/icons/icons/icons8-laptop-play-video-24.png");
  IconLabelContainer* playlists = new IconLabelContainer("Playlists", ":/myplaylist/icons/icons/icons8-playlist-24.png");
  IconLabelContainer* edit = new IconLabelContainer("Playlist edit", ":/myplaylist/icons/icons/icons8-playlistedit-24.png");
  IconLabelContainer* quit = new IconLabelContainer("Quit", ":/myplaylist/icons/icons/icons8-close-24.png");

private slots:
  void disapear();
  void showIt();
};

#endif // SIDEBAR_H
