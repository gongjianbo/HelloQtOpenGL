#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenu>
#include <QAction>

#include "Unit2Demo.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    currentWidget=ui->label;

    ui->menuUnit->addAction("Unit2",[this]{
        setWindowTitle("Unit2");
        if(currentWidget){
            currentWidget->deleteLater();
        }
        currentWidget=new Unit2Demo(this);
        ui->verticalLayout->addWidget(currentWidget);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

