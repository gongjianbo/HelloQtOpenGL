#ifndef UNIT3POLYGONOFFSET_H
#define UNIT3POLYGONOFFSET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_0_Compatibility>

//使用多边形偏移绘制重叠图案
//（在深度缓冲Demo基础上改的，但是感觉没啥突出效果）
//两个实体的某个顶点处于同一位置时，会遇到z冲突
//使用glPolygonOffset函数可以调节片段的深度值而不影响实际位置
class Unit3PolygonOffset : public QOpenGLWidget, protected QOpenGLFunctions_4_0_Compatibility
{
    Q_OBJECT
public:
    explicit Unit3PolygonOffset(QWidget *parent = nullptr);
    ~Unit3PolygonOffset();

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
    //旋转角度
    GLfloat xRotate=5;
    GLfloat yRotate=40;
};

#endif // UNIT3POLYGONOFFSET_H
