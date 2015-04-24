#include "mainwidget.h"
#include "ui_mainwidget.h"

#include "labirintwidget.h"
#include "constaspectratiolayout.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    QLayout *layout = new ConstAspectRatioLayout;
    LabirintWidget *labirintWidget = new LabirintWidget;
    QSizePolicy qsp(QSizePolicy::Preferred,QSizePolicy::Preferred);
    qsp.setHeightForWidth(true);
    labirintWidget->setSizePolicy(qsp);
    layout->addWidget(labirintWidget);
    ui->fieldFrame->setLayout(layout);
}

MainWidget::~MainWidget()
{
    delete ui;
}
