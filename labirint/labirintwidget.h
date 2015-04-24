#pragma once

#include <QWidget>

class Labirint;

class LabirintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LabirintWidget(QWidget *parent = 0);
    ~LabirintWidget();

    int heightForWidth(int w) const;
    bool hasHeightForWidth() const { return true; }

protected:
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    Labirint *m_labirint;
};
