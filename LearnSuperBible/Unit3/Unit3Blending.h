#ifndef UNIT3BLENDING_H
#define UNIT3BLENDING_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_0_Compatibility>

//Blend混合，记得先绘制不透明的，再关掉深度测试绘制混合透明的
//开启混合后，使用glBlendFunc设置混合方式
class Unit3Blending: public QOpenGLWidget, protected QOpenGLFunctions_4_0_Compatibility
{
    Q_OBJECT
public:
    explicit Unit3Blending(QWidget *parent = nullptr);
    ~Unit3Blending();

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

#endif // UNIT3BLENDING_H
