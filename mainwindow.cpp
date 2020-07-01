#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenu>
#include <QAction>

#include "Unit2Demo.h"
#include "Unit3Demo.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    currentWidget=ui->label;

    //单元选择-第2单元
    ui->menuUnit->addAction("Unit2",[this]{
        setWindowTitle("Unit2");
        if(currentWidget){
            currentWidget->deleteLater();
        }
        currentWidget=new Unit2Demo(this);
        ui->verticalLayout->addWidget(currentWidget);
    });
    //单元选择-第3单元
    ui->menuUnit->addAction("Unit3",[this]{
        setWindowTitle("Unit3");
        if(currentWidget){
            currentWidget->deleteLater();
        }
        currentWidget=new Unit3Demo(this);
        ui->verticalLayout->addWidget(currentWidget);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

