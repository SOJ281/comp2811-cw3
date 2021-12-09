#ifndef PLAYLISTCONTAINER_H
#define PLAYLISTCONTAINER_H

#include <QFrame>

class QVBoxLayout;
class QLabel;
class QPushButton;
class QString;
class QCheckBox;

class PlaylistContainer : public QFrame {
public:
  explicit PlaylistContainer(QString playlistName, int videosCount, QString imagePath = "",
                             QFrame *parent = nullptr);

private:
  QVBoxLayout *container;
  QLabel *name;
  QLabel *thumbnail;
  QPushButton *playbutton;
  QLabel *counter;
  QCheckBox *check;
public:
  int vidNumber;

signals:
};

#endif // PLAYLISTCONTAINER_H
