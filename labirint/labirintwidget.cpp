#include "labirintwidget.h"

#include "labirint.h"

#include <QKeyEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPalette>

#include <QDebug>

LabirintWidget::LabirintWidget(QWidget *parent) :
    QWidget(parent)
{
    int w = 40;
    int h = 30;
    m_labirint = new Labirint(w, h);

    m_labirint->generate();

    m_labirint->setCurrent(rand() % w, rand() % h);
    m_labirint->setExit(rand() % w, rand() % h);


    setFocusPolicy(Qt::StrongFocus);
    setAutoFillBackground(true);
    setBackgroundRole(QPalette::Background);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::black);
    setPalette(pal);
}

LabirintWidget::~LabirintWidget()
{
    delete m_labirint;
}

int LabirintWidget::heightForWidth(int w) const
{
    return w * m_labirint->height() / m_labirint->width();
}

void LabirintWidget::loadFromFile(const QString &fileName)
{
    m_labirint->load(fileName.toStdString().c_str());
    updateGeometry();
    update();
}

void LabirintWidget::saveToFile(const QString &fileName)
{
    m_labirint->save(fileName.toStdString().c_str());
    updateGeometry();
    update();
}

void LabirintWidget::regenerate(int width, int height)
{
    m_labirint->generate(width, height);

    m_labirint->setCurrent(rand() % width, rand() % height);
    m_labirint->setExit(rand() % width, rand() % height);
    updateGeometry();
    update();
}

void LabirintWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        m_labirint->moveUp();
        update();
        break;
    case Qt::Key_Down:
        m_labirint->moveDown();
        update();
        break;
    case Qt::Key_Left:
        m_labirint->moveLeft();
        update();
        break;
    case Qt::Key_Right:
        m_labirint->moveRight();
        update();
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

void LabirintWidget::paintEvent(QPaintEvent *event)
{
    const QRect &rect = event->rect();
    if (!rect.isValid())
        return;
    int left = (int)((double) rect.left() / width() * m_labirint->width());
    int top = (int)((double) rect.top() / height() * m_labirint->height());
    int right = (int)((double) rect.right() / width() * m_labirint->width());
    int bottom = (int)((double) rect.bottom() / height() * m_labirint->height());
    if (left < 0) left = 0;
    if (top < 0) top = 0;
    if (right >= m_labirint->width()) right = m_labirint->width() - 1;
    if (bottom >= m_labirint->height()) bottom = m_labirint->height() - 1;

    QPainter painter(this);

    static QPen pen(QBrush(Qt::lightGray), 2);
    painter.setPen(pen);


    static const int traceRectMargin = 3;

    for (int i = left; i <= right; ++i) {
        for (int j = top; j <= bottom; ++j) {
            Place &place = m_labirint->place(i, j);
            QPointF begin((float) i / m_labirint->width() * width(),
                          (float) j / m_labirint->height() * height());
            if (place.leftWall) {
                QPointF end(begin.x(),
                              (float) (j + 1) / m_labirint->height() * height());
                painter.drawLine(begin, end);
            }
            if (place.topWall) {
                QPointF end((float) (i + 1) / m_labirint->width() * width(),
                              begin.y());
                painter.drawLine(begin, end);
            }
            if (m_labirint->trace(i, j) != PlaceNotVisited) {
                QColor traceColor;
                switch (m_labirint->trace(i, j)) {
                case PlaceVisited:
                    traceColor = Qt::darkRed;
                    break;
                case PlacePath:
                    traceColor = Qt::green;
                    break;
                }
                painter.fillRect((float) i / m_labirint->width() * width() + traceRectMargin,
                                 (float) j / m_labirint->height() * height() + traceRectMargin,
                                 (float) width() / m_labirint->width() - traceRectMargin * 2,
                                 (float) height() / m_labirint->height() - traceRectMargin * 2, traceColor);
            }
        }
    }

    int exitX = m_labirint->exitX();
    int exitY = m_labirint->exitY();
    static const int exitRectMargin = 2;

    if (exitX >= left && exitX <= right && exitY >= top && exitY <= bottom) {
        painter.fillRect((float) exitX / m_labirint->width() * width() + exitRectMargin,
                         (float) exitY / m_labirint->height() * height() + exitRectMargin,
                         (float) width() / m_labirint->width() - exitRectMargin * 2,
                         (float) height() / m_labirint->height() - exitRectMargin * 2, Qt::cyan);
    }

    int curX = m_labirint->currentX();
    int curY = m_labirint->currentY();
    static const int curRectMargin = 2;

    if (curX >= left && curX <= right && curY >= top && curY <= bottom) {
        painter.fillRect((float) curX / m_labirint->width() * width() + curRectMargin,
                         (float) curY / m_labirint->height() * height() + curRectMargin,
                         (float) width() / m_labirint->width() - curRectMargin * 2,
                         (float) height() / m_labirint->height() - curRectMargin * 2, Qt::magenta);
    }
}
