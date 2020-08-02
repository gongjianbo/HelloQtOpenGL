#ifndef UNIT3MULTISAMPLE_H
#define UNIT3MULTISAMPLE_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_0_Compatibility>

//多重采样
//点和线的平滑处理得到广泛支持，但是多边形支持不好，这时可以采用多重采样来解决
//如果没有多重采样缓冲区，GL_MULTISAMPLE当作被禁止的
//Qt中需要配合QSurfaceFormat设置采样
//启用多重采样时，平滑会被忽略，可以先后分开绘制
class Unit3MultiSample : public QOpenGLWidget, protected QOpenGLFunctions_4_0_Compatibility
{
    Q_OBJECT
public:
    explicit Unit3MultiSample(QWidget *parent = nullptr);
    ~Unit3MultiSample();

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
    //开关，按空格切换状态
    bool sampleOn=true;
};

#endif // UNIT3MULTISAMPLE_H
