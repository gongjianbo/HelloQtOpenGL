#ifndef UNIT1TRIANGLE_H
#define UNIT1TRIANGLE_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>

//使用Qt+OpenGL 4.5 core绘制一个三角
class Unit1Triangle : public QOpenGLWidget, protected QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    explicit Unit1Triangle(QWidget *parent = nullptr);
    ~Unit1Triangle();

protected:
    //设置OpenGL资源和状态。在第一次调用resizeGL或paintGL之前被调用一次
    void initializeGL() override;
    //渲染OpenGL场景，每当需要更新小部件时使用
    void paintGL() override;
    //设置OpenGL视口、投影等，每当尺寸大小改变时调用
    void resizeGL(int width, int height) override;

private:
    //VAO是一个对象，其中包含一个或者更多的Vertex Buffer Objects。
    //而VBO是Graphics Card中的一个内存缓冲区，用来保存顶点信息，颜色信息，法线信息，纹理坐标信息和索引信息等等。
    //一个VAO有多个VBO，它们之间也是通过上下文，只有唯一的激活VAO，在VAO后创建的VBO都属于该VAO。
    //关联VBO数据用取得当前激活的缓存区对象偏移来指定。

    //顶点数组对象
    GLuint vao[1];
    //缓存对象 vbo
    GLuint buffer[1];
    //着色器程序对象
    GLuint shaderProgram;
};

#endif // UNIT1TRIANGLE_H
