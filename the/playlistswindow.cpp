#include "playlistswindow.h"
#include "iconlabelcontainer.h"
#include "playlistcontainer.h"
#include "scrollgridlayout.h"
#include "sidebar.h"
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QString>

PlaylistsWindow::PlaylistsWindow(QWidget *parent) : QWidget(parent) {
  createWidgets();
  arrangeWidgets();
  makeConnections();
  setMinimumSize(800, 600);
  setWindowTitle("playlists");
}

void PlaylistsWindow::createWidgets() {
  sort = new QComboBox();
  const QStringList list{"Sort by: name", "Sort by: creation date", "Sort by: last played",
                         "Sort by: video count"};
  sort->addItems(list);
  sort->setFixedSize(130, 36);
  sort->setStyleSheet("QComboBox {border: 1px solid; border-radius: 4px; background-color: #ffe0ba;} QComboBox QAbstractItemView {background-color: #ffe0ba;};");

  searchQuery = new QLineEdit();
  searchQuery->setFixedHeight(36);
  searchQuery->setStyleSheet("border: 1px solid; border-radius: 4px; border-top-right-radius: 0px; "
                             "border-bottom-right-radius: 0px; background-color: white;");

  search = new QPushButton("Search");
  search->setFixedSize(40, 36);
  search->setStyleSheet("border: 1px solid; border-radius: 4px; border-left: 0px; "
                        "border-top-left-radius: 0px; border-bottom-left-radius: 0px;background-color:#ffe0ba;");

  scroll = new QScrollArea();
  scroll->setStyleSheet("background-color: #ffc070;");
  scrollAreaContents = new QWidget();
  scroll->setFrameShape(QFrame::NoFrame);
  scroll->setWidgetResizable(true);
  scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void PlaylistsWindow::arrangeWidgets() {

  // Divide window in left toolbar area and remaining area
  auto *mainLayout = new QHBoxLayout();
  auto *centerLayout = new QVBoxLayout();

  // Populate left toolbar

  // Add left toolbar to left part of the window
  //mainLayout->addWidget(new SideBar());

  // Add the other parts
  mainLayout->addLayout(centerLayout);

  // Divide center layout in top header and body

  // Header stuff
  auto *header = new QHBoxLayout();
  header->addWidget(sort);

  // Container widget for searchQuery and its button search
  auto *container = new QWidget();
  container->setFixedHeight(40);
  auto *containerLayout = new QHBoxLayout();
  containerLayout->setSpacing(0);
  containerLayout->setContentsMargins(0, 0, 0, 0);
  containerLayout->addWidget(searchQuery);
  containerLayout->addWidget(search);
  container->setLayout(containerLayout);
  header->addWidget(container);

  // Body stuff
  auto *body = new QHBoxLayout();

  // Scroll
  ScrollGridLayout *scrollAreaContentsLayout = nullptr;
  scroll->setWidget(scrollAreaContents);
  // Setup scrollarea
  randomPlaylists(scrollAreaContentsLayout);

  body->addWidget(scroll);

  // Add header & body to center
  centerLayout->addLayout(header);
  centerLayout->addLayout(body);

  setLayout(mainLayout);
}

void PlaylistsWindow::makeConnections() {
  connect(sort, SIGNAL(currentIndexChanged(int)), this, SLOT(fakeSort(int)));
  connect(search, SIGNAL(clicked(bool)), this, SLOT(fakeFilter()));
}

// Shitty way to generate a pseudo-random number but I don't care
inline int PlaylistsWindow::randomNumber(int max) { return (rand() % max) + 1; }

// This sort just changes the playlists randomly, lol
void PlaylistsWindow::fakeSort(int index) { randomPlaylists(scroll->widget()->layout(), false); }

// It just displays 2 random playlists
void PlaylistsWindow::fakeFilter() {
  // If it's empty, just regenerate the whole thing
  if (searchQuery->text() != "")
    randomPlaylists(scroll->widget()->layout(), false, 2);
  else
    randomPlaylists(scroll->widget()->layout(), true);
}

void PlaylistsWindow::randomPlaylists(QLayout *scrollAreaContentsLayout, bool order, int number) {

  // Check for nullptr
  if (scrollAreaContentsLayout)
    deleteLayout(scrollAreaContentsLayout);

  scrollAreaContentsLayout = new ScrollGridLayout(0);

  // Set this layout as the scollAreaContent's layout
  scroll->widget()->setLayout(scrollAreaContentsLayout);

  // Populate the layout with mock playlists
  int it = 0;
  for (int i = 0; i < number; ++i) {
    ++it;
    PlaylistContainer *mockPlaylist;
    if (order)
      mockPlaylist = new PlaylistContainer("myPlaylist " + QString::number(it), randomNumber(100));
    else
      mockPlaylist = new PlaylistContainer("myPlaylist " + QString::number(randomNumber(100)),
                                           randomNumber(100));
    scrollAreaContentsLayout->addWidget(mockPlaylist);
  }
}

void PlaylistsWindow::deleteLayout(QLayout *layout) {
  // Deleting a layout does not delete its child widgets by default
  QLayout *sublayout;
  QWidget *widget;

  // Delete all its children until it's empty
  while (!layout->isEmpty()) {
    auto item = layout->takeAt(0);
    // If it's a nested layout, recursive call
    if ((sublayout = item->layout()) != 0)
      deleteLayout(sublayout);
    // If it's a widget, hide it and delete it
    else if ((widget = item->widget()) != 0) {
      widget->hide();
      delete widget;
    }
    // Otherwise just delete it
    else
      delete item;
  }

  // Finally, delete the layout
  delete layout;
}

void PlaylistsWindow::disapear() {
    hide();
}
void PlaylistsWindow::showIt() {
    show();
}
