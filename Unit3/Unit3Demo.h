#ifndef UNIT3DEMO_H
#define UNIT3DEMO_H

#include <QWidget>

namespace Ui {
class Unit3Demo;
}

//第三单元Demo展示
class Unit3Demo : public QWidget
{
    Q_OBJECT

public:
    explicit Unit3Demo(QWidget *parent = nullptr);
    ~Unit3Demo();

private:
    Ui::Unit3Demo *ui;
};

#endif // UNIT3DEMO_H
