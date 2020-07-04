#ifndef UNIT3CULLFACE_H
#define UNIT3CULLFACE_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_0_Compatibility>

//使用面剔除绘制立体图元
class Unit3CullFace : public QOpenGLWidget, protected QOpenGLFunctions_4_0_Compatibility
{
    Q_OBJECT
public:
    explicit Unit3CullFace(QWidget *parent = nullptr);
    ~Unit3CullFace();

protected:
    //设置OpenGL资源和状态。在第一次调用resizeGL或paintGL之前被调用一次
    void initializeGL() override;
    //渲染OpenGL场景，每当需要更新小部件时使用
    void paintGL() override;
    //设置OpenGL视口、投影等，每当尺寸大小改变时调用
    void resizeGL(int width, int height) override;

    //按键事件
    void keyPressEvent(QKeyEvent *event) override;

private:
    //旋转角度
    GLfloat xRotate=0;
    GLfloat yRotate=0;
};

#endif // UNIT3CULLFACE_H
