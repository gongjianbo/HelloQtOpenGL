#include "Unit1Demo.h"
#include "ui_Unit1Demo.h"

Unit1Demo::Unit1Demo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Unit1Demo)
{
    ui->setupUi(this);
}

Unit1Demo::~Unit1Demo()
{
    delete ui;
}
