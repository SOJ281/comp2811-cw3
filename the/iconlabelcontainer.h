#ifndef ICONLABELCONTAINER_H
#define ICONLABELCONTAINER_H

#include <QWidget>

class QVBoxLayout;
class QLabel;
class QString;

class IconLabelContainer : public QWidget {
  Q_OBJECT
public:
  explicit IconLabelContainer(QString text, QString imagePath, QWidget *parent = nullptr);

private:
  QVBoxLayout *container;
  QLabel *icon;
  QLabel *label;

signals:
public slots:
};

#endif // ICONLABELCONTAINER_H
