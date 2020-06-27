#ifndef UNIT2DEMO_H
#define UNIT2DEMO_H

#include <QWidget>

namespace Ui {
class Unit2Demo;
}

//第二单元Demo展示
class Unit2Demo : public QWidget
{
    Q_OBJECT

public:
    explicit Unit2Demo(QWidget *parent = nullptr);
    ~Unit2Demo();

private:
    Ui::Unit2Demo *ui;
};

#endif // UNIT2DEMO_H
