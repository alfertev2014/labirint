#include "mainwidget.h"
#include "ui_mainwidget.h"

#include "labirintwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    QVBoxLayout *layout = new QVBoxLayout;
    LabirintWidget *labirintWidget = new LabirintWidget;
    layout->addWidget(labirintWidget);
    ui->fieldFrame->setLayout(layout);
}

MainWidget::~MainWidget()
{
    delete ui;
}
