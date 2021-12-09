#ifndef PLAYLISTSWINDOW_H
#define PLAYLISTSWINDOW_H

#include <QWidget>
#include <QtWidgets>

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
  inline int randomNumber(int max);
signals:
};

#endif // PLAYLISTSWINDOW_H
