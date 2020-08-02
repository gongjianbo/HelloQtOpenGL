#ifndef UNIT3SMOOTH_H
#define UNIT3SMOOTH_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_0_Compatibility>

//Smooth抗锯齿，需要开启混合
//点和线的平滑处理得到广泛支持，但是多边形支持不好，可以采用多重采样来解决
//（窗口初始化的时候貌似被多重采样设置影响了）
class Unit3Smooth : public QOpenGLWidget, protected QOpenGLFunctions_4_0_Compatibility
{
    Q_OBJECT
public:
    explicit Unit3Smooth(QWidget *parent = nullptr);
    ~Unit3Smooth();

protected:
    //设置OpenGL资源和状态。在第一次调用resizeGL或paintGL之前被调用一次
    void initializeGL() override;
    //渲染OpenGL场景，每当需要更新小部件时使用
    void paintGL() override;
    //设置OpenGL视口、投影等，每当尺寸大小改变时调用
    void resizeGL(int width, int height) override;

    //设置切换显示的时候获取焦点
    void showEvent(QShowEvent *event) override;
    //按键事件
    void keyPressEvent(QKeyEvent *event) override;

private:
    //抗锯齿开关，按空格切换状态
    bool smoothOn=true;
};

#endif // UNIT3SMOOTH_H
