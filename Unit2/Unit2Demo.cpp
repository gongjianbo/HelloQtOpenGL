#include "Unit2Demo.h"
#include "ui_Unit2Demo.h"

Unit2Demo::Unit2Demo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Unit2Demo)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_StyledBackground);
}

Unit2Demo::~Unit2Demo()
{
    delete ui;
}
