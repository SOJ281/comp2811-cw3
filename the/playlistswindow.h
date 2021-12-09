#ifndef PLAYLISTSWINDOW_H
#define PLAYLISTSWINDOW_H

#include <QWidget>
class QComboBox;
class QLineEdit;
class QPushButton;
class QScrollArea;
class QWidget;

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
  void randomPlaylists(QLayout *scrollAreaContentsLayout, bool order = true, int number = 24);
  void deleteLayout(QLayout *layout);

private slots:
  void fakeSort(int index);
  void fakeFilter();
  void disapear();
  void showIt();
signals:
};

#endif // PLAYLISTSWINDOW_H
