#include "Unit3Demo.h"
#include "ui_Unit3Demo.h"

Unit3Demo::Unit3Demo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Unit3Demo)
{
    ui->setupUi(this);

    ui->tabWidget->setCurrentIndex(0);
}

Unit3Demo::~Unit3Demo()
{
    delete ui;
}
