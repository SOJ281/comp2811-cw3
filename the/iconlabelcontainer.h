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
  void clicked();
public slots:
private slots:
  void disapear();
  void showIt();
protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // ICONLABELCONTAINER_H
