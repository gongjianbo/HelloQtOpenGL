#ifndef UNIT4MODELVIEW_H
#define UNIT4MODELVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_0_Compatibility>

//模型视图投影
class Unit4ModelView : public QOpenGLWidget, protected QOpenGLFunctions_4_0_Compatibility
{
    Q_OBJECT
public:
    explicit Unit4ModelView(QWidget *parent = nullptr);
    ~Unit4ModelView();

protected:
    //设置OpenGL资源和状态。在第一次调用resizeGL或paintGL之前被调用一次
    void initializeGL() override;
    //渲染OpenGL场景，每当需要更新小部件时使用
    void paintGL() override;
    //设置OpenGL视口、投影等，每当尺寸大小改变时调用
    void resizeGL(int width, int height) override;

    //设置切换显示的时候获取焦点
    void showEvent(QShowEvent *event) override;

private:
    //自定义透视投影
    void MyPerspective(double fovy, double aspect, double zNear, double zFar);

private:
    //旋转角度
    int yRotate = 0;
};

#endif // UNIT4MODELVIEW_H
