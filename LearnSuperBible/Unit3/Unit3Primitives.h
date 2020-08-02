#ifndef UNIT3PRIMITIVES_H
#define UNIT3PRIMITIVES_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_0_Compatibility>

//展示基本图元
class Unit3Primitives : public QOpenGLWidget, protected QOpenGLFunctions_4_0_Compatibility
{
    Q_OBJECT
public:
    explicit Unit3Primitives(QWidget *parent = nullptr);
    ~Unit3Primitives();

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
    //测试几种图元模式，Qt中有十种枚举，教程中只列了7中
    //GL_POINTS  点集
    void drawPoints();
    //GL_LINES  线集
    void drawLines();
    //GL_LINE_LOOP  连线-首位相连
    void drawLineLoop();
    //GL_LINE_STRIP  连线-首位未相连
    void drawLineStrip();
    //GL_TRIANGLES  三角形
    void drawTriangles();
    void drawTriangles2();
    //GL_TRIANGLE_STRIP  三角带
    void drawTrianglesStrip();
    //GL_TRIANGLE_FAN  扇形
    void drawTrianglesFan();

private:
    //旋转角度
    GLfloat xRotate=0;
    GLfloat yRotate=0;
    //绘制类型选择-标值位
    int drawType=GL_POINTS;
};

#endif // UNIT3PRIMITIVES_H
