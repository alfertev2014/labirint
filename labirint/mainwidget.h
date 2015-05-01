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

private slots:
    void on_generateButton_clicked();

    void on_openButton_clicked();

    void on_saveButton_clicked();

    void onExitReached();

private:
    Ui::MainWidget *ui;

    LabirintWidget *m_labirintWidget;
};
