#pragma once

#include <QWidget>


namespace Ui {
class MainWidget;
}

class LabirintWidget;

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private:
    Ui::MainWidget *ui;
};
