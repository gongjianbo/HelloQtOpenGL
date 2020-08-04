#ifndef UNIT1DEMO_H
#define UNIT1DEMO_H

#include <QWidget>

namespace Ui {
class Unit1Demo;
}

class Unit1Demo : public QWidget
{
    Q_OBJECT

public:
    explicit Unit1Demo(QWidget *parent = nullptr);
    ~Unit1Demo();

private:
    Ui::Unit1Demo *ui;
};

#endif // UNIT1DEMO_H
