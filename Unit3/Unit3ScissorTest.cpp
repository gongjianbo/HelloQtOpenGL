#include "Unit3ScissorTest.h"

#include <QVector3D>
#include <QtMath>
#include <QDebug>

Unit3ScissorTest::Unit3ScissorTest(QWidget *parent)
    : QOpenGLWidget(parent)
{
    //默认没得焦点，没法接收按键
    setFocusPolicy(Qt::StrongFocus);
}

Unit3ScissorTest::~Unit3ScissorTest()
{
    //此为Qt接口:通过使相应的上下文成为当前上下文并在该上下文中绑定帧缓冲区对象，
    //准备为此小部件呈现OpenGL内容。在调用paintGL()之前会自动调用。
    makeCurrent();

    //.. ...

    //此为Qt接口:释放上下文。在大多数情况下不需要调用此函数，
    //因为小部件将确保在调用paintGL()时正确绑定和释放上下文。
    doneCurrent();
}

void Unit3ScissorTest::initializeGL()
{
    //此为Qt接口:为当前上下文初始化OpenGL函数解析
    initializeOpenGLFunctions();
}

void Unit3ScissorTest::paintGL()
{
    //使用黑色clear
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //清除颜色缓冲区
    glClear(GL_COLOR_BUFFER_BIT);

    //开启裁剪
    glEnable(GL_SCISSOR_TEST);

    //【1】
    //裁剪区域clear red
    glClearColor(1.0f,0.0f,0.0f,1.0f);
    //X,Y,WIDTH,HEIGHT
    glScissor(10,20,100,200); //裁剪的坐标貌似是窗口上的，原点靠左下角
    glClear(GL_COLOR_BUFFER_BIT);

    //【2】
    //裁剪区域clear green
    glClearColor(0.0f,1.0f,0.0f,1.0f);
    //X,Y,WIDTH,HEIGHT
    glScissor(width()-100-10,height()-200-20,100,200);
    glClear(GL_COLOR_BUFFER_BIT);

    //关闭裁剪
    glDisable(GL_SCISSOR_TEST);
}

void Unit3ScissorTest::resizeGL(int width, int height)
{
    //视口，靠左下角缩放
    glViewport(0,0,width,height);
}

void Unit3ScissorTest::showEvent(QShowEvent *event)
{
    setFocus();
    QOpenGLWidget::showEvent(event);
}
