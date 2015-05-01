#include "mainwidget.h"
#include "ui_mainwidget.h"

#include "labirintwidget.h"
#include "constaspectratiolayout.h"

#include <QFileDialog>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    QLayout *layout = new ConstAspectRatioLayout;
    m_labirintWidget = new LabirintWidget;
    QSizePolicy qsp(QSizePolicy::Preferred,QSizePolicy::Preferred);
    qsp.setHeightForWidth(true);
    m_labirintWidget->setSizePolicy(qsp);
    layout->addWidget(m_labirintWidget);
    ui->fieldFrame->setLayout(layout);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_generateButton_clicked()
{
    int width = ui->widthSpinBox->value();
    int height = ui->heightSpinBox->value();
    m_labirintWidget->regenerate(width, height);
}

void MainWidget::on_openButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        m_labirintWidget->loadFromFile(fileName);
}

void MainWidget::on_saveButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    if (!fileName.isEmpty())
        m_labirintWidget->saveToFile(fileName);
}
