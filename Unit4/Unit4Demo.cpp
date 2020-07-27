#include "Unit4Demo.h"
#include "ui_Unit4Demo.h"

Unit4Demo::Unit4Demo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Unit4Demo)
{
    ui->setupUi(this);

    ui->tabWidget->setCurrentIndex(0);
}

Unit4Demo::~Unit4Demo()
{
    delete ui;
}
