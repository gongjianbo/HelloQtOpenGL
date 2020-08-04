#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenu>
#include <QAction>

#include "Unit1Demo.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    currentWidget=ui->label;

    //单元选择-第1单元
    ui->menuUnit->addAction("Unit1",[this]{
        setWindowTitle("Unit1");
        if(currentWidget){
            currentWidget->deleteLater();
        }
        currentWidget=new Unit1Demo(this);
        ui->verticalLayout->addWidget(currentWidget);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

