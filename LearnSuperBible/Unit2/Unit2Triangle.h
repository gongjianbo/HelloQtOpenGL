#ifndef UNIT2TRIANGLE_H
#define UNIT2TRIANGLE_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_0_Compatibility>
#include <QTimer>

//绘制三角（使用固定管线）
//Compatibility是为了支持固定管线API
class Unit2Triangle : public QOpenGLWidget, protected QOpenGLFunctions_4_0_Compatibility
{
    Q_OBJECT
public:
    explicit Unit2Triangle(QWidget *parent = nullptr);
    ~Unit2Triangle();

protected:
    //设置OpenGL资源和状态。在第一次调用resizeGL或paintGL之前被调用一次
    void initializeGL() override;
    //渲染OpenGL场景，每当需要更新小部件时使用
    void paintGL() override;
    //设置OpenGL视口、投影等，每当尺寸大小改变时调用
    void resizeGL(int width, int height) override;

private:
    //定时器，用于颜色渐变
    QTimer *timer=new QTimer(this);
    //颜色偏移值
    int offsetCount=0;
    //累加或减
    bool offsetFlag=false;
};

#endif // UNIT2TRIANGLE_H
