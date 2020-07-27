#ifndef UNIT4DEMO_H
#define UNIT4DEMO_H

#include <QWidget>

namespace Ui {
class Unit4Demo;
}

class Unit4Demo : public QWidget
{
    Q_OBJECT

public:
    explicit Unit4Demo(QWidget *parent = nullptr);
    ~Unit4Demo();

private:
    Ui::Unit4Demo *ui;
};

#endif // UNIT4DEMO_H
