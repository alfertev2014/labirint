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

    void loadFromFile(const QString &fileName);
    void saveToFile(const QString &fileName);
    void regenerate(int width, int height);

signals:
    void exitReached();

protected:
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    Labirint *m_labirint;
};
