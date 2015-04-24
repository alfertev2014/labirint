#pragma once

#include <QLayout>

class ConstAspectRatioLayout : public QLayout
{
    Q_OBJECT
public:
    explicit ConstAspectRatioLayout(QWidget *parent = 0);

    void addItem(QLayoutItem *item);
    int count() const;
    QLayoutItem *itemAt(int index) const;
    QLayoutItem *takeAt(int index);

    void setGeometry(const QRect &r);
    QSize sizeHint() const;

private:
    QLayoutItem *m_item;
};
