#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
class QHBoxLayout;

class SideBar : public QWidget {
public:
  explicit SideBar(QWidget *parent = nullptr);

private:
  void createWidgets();
  void arrangeWidgets();
  void makeConnections();
  QHBoxLayout *horizontal;
};

#endif // SIDEBAR_H
