#ifndef PLAYLISTSWINDOW_H
#define PLAYLISTSWINDOW_H

#include <QWidget>
#include <QtWidgets>
#include "playlistcontainer.h"

class PlaylistsWindow : public QWidget {
  Q_OBJECT
public:
  explicit PlaylistsWindow(QWidget *parent = nullptr);

private:
  void createWidgets();
  void arrangeWidgets();
  void makeConnections();
  QComboBox *sort;
  QLineEdit *searchQuery;
  QPushButton *search;
  QScrollArea *scroll;
  QWidget *scrollAreaContents;
  std::vector<PlaylistContainer*> playLists;
  inline int randomNumber(int max);
signals:

private slots:
  void disapear();
  void showIt();
  void sortBy(QString criteria);
};

#endif // PLAYLISTSWINDOW_H
