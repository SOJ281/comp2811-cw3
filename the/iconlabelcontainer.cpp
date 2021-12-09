#include "iconlabelcontainer.h"
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>

IconLabelContainer::IconLabelContainer(QString text, QString imagePath, QWidget *parent)
    : QWidget(parent) {
  this->setCursor(Qt::PointingHandCursor);
  container = new QVBoxLayout(this);
  // composite widget wastes no space
  container->setContentsMargins(0, 20, 20, 0);

  icon = new QLabel();
  icon->setFixedSize(24, 24);
  icon->setPixmap(QPixmap(imagePath));
  label = new QLabel(text);

  container->addWidget(icon);
  container->addWidget(label);
}

void IconLabelContainer::mousePressEvent(QMouseEvent* event) {
    emit clicked();
}

void IconLabelContainer::disapear() {
    hide();
}
void IconLabelContainer::showIt() {
    show();
}
