#pragma once

#include <QWidget>

class Labirint;

class LabirintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LabirintWidget(QWidget *parent = 0);
    ~LabirintWidget();

protected:
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    Labirint *m_labirint;
};
