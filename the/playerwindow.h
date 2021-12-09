#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H



#include <QWidget>
#include <QtWidgets>


#include <iostream>
#include <QApplication>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlaylist>
#include <string>
#include <vector>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtCore/QFileInfo>
#include <QtWidgets/QFileIconProvider>
#include <QDesktopServices>
#include <QImageReader>
#include <QMessageBox>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include "the_player.h"
#include "the_button.h"

#include <string>
#include <QLineEdit>
#include <QtWidgets>
#include <QFont>
#include <QRect>
#include "video_scroll.h"
#include "playlistswindow.h"
#include "sidebar.h"
#include "iconlabelcontainer.h"

class PlayerWindow : public QWidget {
  Q_OBJECT
public:
  explicit PlayerWindow(QWidget *parent = nullptr);
  void assemble(int argc, char *argv[]);
  // collect all the videos in the folder
  std::vector<TheButtonInfo> videos;

private:
  std::vector<TheButtonInfo> getInfoIn (std::string loc);
  std::vector<TheButtonInfo> getInfo (std::string loc);
signals:

private slots:
  void disapear();
  void showIt();
};

#endif // PLAYERWINDOW_H
