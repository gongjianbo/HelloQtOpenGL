#include "Unit2Triangle.h"

Unit2Triangle::Unit2Triangle(QWidget *parent)
    : QOpenGLWidget(parent)
{

}

Unit2Triangle::~Unit2Triangle()
{
    //此为Qt接口:通过使相应的上下文成为当前上下文并在该上下文中绑定帧缓冲区对象，
    //准备为此小部件呈现OpenGL内容。在调用paintGL()之前会自动调用。
    makeCurrent();

    //.. ...

    //此为Qt接口:释放上下文。在大多数情况下不需要调用此函数，
    //因为小部件将确保在调用paintGL()时正确绑定和释放上下文。
    doneCurrent();
}

void Unit2Triangle::initializeGL()
{
    //此为Qt接口:为当前上下文初始化OpenGL函数解析
    initializeOpenGLFunctions();
    //窗口清除的颜色
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
}

void Unit2Triangle::paintGL()
{
    //【主要部分】
    //清除颜色缓冲区
    glClear(GL_COLOR_BUFFER_BIT);

    //绘制三角(坐标范围默认为[-1,1])
    glColor3f(1.0f,1.0f,0.1f);
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.5f,0.0f,0.0f); //三角形的三个顶点
    glVertex3f(0.5f,0.0f,0.0f);
    glVertex3f( 0.0f,0.5f,0.0f );
    glEnd();
}

void Unit2Triangle::resizeGL(int width, int height)
{
    //视口，靠左下角缩放
    glViewport(0,0,width,height);
}
