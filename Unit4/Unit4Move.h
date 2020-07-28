#ifndef UNIT4MOVE_H
#define UNIT4MOVE_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_0_Compatibility>
#include <QMatrix4x4>
#include <QVector3D>

//按键移动物体
class Unit4Move : public QOpenGLWidget, protected QOpenGLFunctions_4_0_Compatibility
{
    Q_OBJECT
public:
    explicit Unit4Move(QWidget *parent = nullptr);
    ~Unit4Move();

protected:
    //设置OpenGL资源和状态。在第一次调用resizeGL或paintGL之前被调用一次
    void initializeGL() override;
    //渲染OpenGL场景，每当需要更新小部件时使用
    void paintGL() override;
    //设置OpenGL视口、投影等，每当尺寸大小改变时调用
    void resizeGL(int width, int height) override;

    //按键事件
    void keyPressEvent(QKeyEvent *event) override;
    //设置切换显示的时候获取焦点
    void showEvent(QShowEvent *event) override;

private:
    //顶点列表
    QList<QVector3D> vertexList;
    //移动
    float xOffset=0;
    float yOffset=0;
};

#endif // UNIT4MOVE_H
