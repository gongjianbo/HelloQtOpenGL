#ifndef UNIT3SCISSORTEST_H
#define UNIT3SCISSORTEST_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_0_Compatibility>

//使用裁剪测试刷新部分区域
//裁剪的坐标貌似是窗口上的，原点靠左下角
class Unit3ScissorTest: public QOpenGLWidget, protected QOpenGLFunctions_4_0_Compatibility
{
    Q_OBJECT
public:
    explicit Unit3ScissorTest(QWidget *parent = nullptr);
    ~Unit3ScissorTest();

protected:
    //设置OpenGL资源和状态。在第一次调用resizeGL或paintGL之前被调用一次
    void initializeGL() override;
    //渲染OpenGL场景，每当需要更新小部件时使用
    void paintGL() override;
    //设置OpenGL视口、投影等，每当尺寸大小改变时调用
    void resizeGL(int width, int height) override;

    //设置切换显示的时候获取焦点
    void showEvent(QShowEvent *event) override;
};

#endif // UNIT3SCISSORTEST_H
