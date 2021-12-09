#ifndef SCROLLGRIDLAYOUT_H
#define SCROLLGRIDLAYOUT_H

#include <QLayout>
#include <QList>

class ScrollGridLayout : public QLayout {

public:
  ScrollGridLayout(int spacing) : QLayout() { setSpacing(spacing); }
  ScrollGridLayout(int spacing, QWidget *parent) : QLayout(parent) { setSpacing(spacing); }
  ~ScrollGridLayout();

  // standard functions for a QLayout
  void setGeometry(const QRect &rect) override;

  void addItem(QLayoutItem *item) override;
  QSize sizeHint() const override;
  QSize minimumSize() const override;
  int count() const override;
  QLayoutItem *itemAt(int) const override;
  QLayoutItem *takeAt(int) override;

private:
  QList<QLayoutItem *> list_;

  int widgetSpace(int width) const;
};

#endif // SCROLLGRIDLAYOUT_H
