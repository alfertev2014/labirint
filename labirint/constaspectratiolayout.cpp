#include "constaspectratiolayout.h"

#include <QObject>

ConstAspectRatioLayout::ConstAspectRatioLayout(QWidget *parent) :
    QLayout(parent), m_item(0)
{
}

void ConstAspectRatioLayout::addItem(QLayoutItem *item)
{
    delete m_item;
    m_item = item;
}

int ConstAspectRatioLayout::count() const
{
    return m_item ? 1 : 0;
}

QLayoutItem *ConstAspectRatioLayout::itemAt(int index) const
{
    return index == 0 ? m_item : 0;
}

QLayoutItem *ConstAspectRatioLayout::takeAt(int index)
{
    return index == 0 ? m_item : 0;
}

void ConstAspectRatioLayout::setGeometry(const QRect &r)
{
    QLayout::setGeometry(r);
    if (m_item->hasHeightForWidth()) {
        int height = m_item->heightForWidth(r.width());
        if (height > r.height()) {
            int width = r.height() * r.width() / height;
            QRect itemRect((r.width() - width) / 2, 0, width, r.height());
            m_item->setGeometry(itemRect);
        }
        else {
            QRect itemRect(0, (r.height() - height) / 2, r.width(), height);
            m_item->setGeometry(itemRect);
        }
    }
}

QSize ConstAspectRatioLayout::sizeHint() const
{
    return m_item->sizeHint();
}
