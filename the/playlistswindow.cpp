#include "playlistswindow.h"
#include "iconlabelcontainer.h"
#include "playlistcontainer.h"
#include "scrollgridlayout.h"
#include "sidebar.h"

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
  sort->setFixedSize(120, 36);
  sort->setStyleSheet("QComboBox {border: 1px solid; border-radius: 4px;}");

  searchQuery = new QLineEdit();
  searchQuery->setFixedHeight(36);
  searchQuery->setStyleSheet("border: 1px solid; border-radius: 4px; border-top-right-radius: 0px; "
                             "border-bottom-right-radius: 0px;");

  search = new QPushButton("Search");
  search->setFixedSize(40, 36);
  search->setStyleSheet("border: 1px solid; border-radius: 4px; border-left: 0px; "
                        "border-top-left-radius: 0px; border-bottom-left-radius: 0px;");

  scroll = new QScrollArea();
  scrollAreaContents = new QWidget();
}

void PlaylistsWindow::arrangeWidgets() {

  // Divide window in left toolbar area and remaining area
  auto *mainLayout = new QHBoxLayout();
  //auto *leftToolBar = new QVBoxLayout();
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

  // Setup scrollarea
  auto *scrollAreaContentsLayout = new ScrollGridLayout(0);

  scrollAreaContents->setLayout(scrollAreaContentsLayout);


  int it = 0;
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 3; ++j) {
      ++it;
      auto *mockPlaylist =
          new PlaylistContainer("myPlaylist " + QString::number(it), randomNumber(100));
      // mockPlaylist->setFixedSize(300, 200);
      playLists.push_back(mockPlaylist);
      scrollAreaContentsLayout->addWidget(mockPlaylist);
    }
  }

  scroll->setWidget(scrollAreaContents);
  scroll->setFrameShape(QFrame::NoFrame);
  scroll->setWidgetResizable(true);
  scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  body->addWidget(scroll);

  // Add header & body to center
  centerLayout->addLayout(header);
  centerLayout->addLayout(body);

  setLayout(mainLayout);
}

void PlaylistsWindow::disapear() {
    hide();
}
void PlaylistsWindow::showIt() {
    show();
}

void PlaylistsWindow::sortBy(QString criteria) {
    for(PlaylistContainer* i : playLists) {
        scrollAreaContents->layout()->removeWidget(i);
    }
    delete scrollAreaContents->layout();
    auto *scrollAreaContentsLayout = new ScrollGridLayout(0);

    scrollAreaContents->setLayout(scrollAreaContentsLayout);

    if (!criteria.compare("Sort by: video count")) {
        int i, j;
        PlaylistContainer* key;
        int n = sizeof(playLists) / sizeof(playLists[0]);
        for (i = 1; i < sizeof(playLists); i++){
            key = playLists[i];
            j = i - 1;
            while (j >= 0 && playLists[j]->vidNumber > key->vidNumber) {
                playLists[j + 1] = playLists[j];
                j = j - 1;
            }
            playLists[j + 1] = key;
        }
    }
    for(PlaylistContainer* i : playLists) {
        scrollAreaContentsLayout->addWidget(i);
    }
}

void PlaylistsWindow::makeConnections() {
    connect(sort, SIGNAL(currentTextChanged(QString)), this, SLOT(sortBy(QString)));
}

inline int PlaylistsWindow::randomNumber(int max) { return (rand() % max) + 1; }
