#include "Unit3Blending.h"

#include <QVector3D>
#include <QtMath>
#include <QDebug>

Unit3Blending::Unit3Blending(QWidget *parent)
    : QOpenGLWidget(parent)
{
    //默认没得焦点，没法接收按键
    setFocusPolicy(Qt::StrongFocus);
}

Unit3Blending::~Unit3Blending()
{
    //此为Qt接口:通过使相应的上下文成为当前上下文并在该上下文中绑定帧缓冲区对象，
    //准备为此小部件呈现OpenGL内容。在调用paintGL()之前会自动调用。
    makeCurrent();

    //.. ...

    //此为Qt接口:释放上下文。在大多数情况下不需要调用此函数，
    //因为小部件将确保在调用paintGL()时正确绑定和释放上下文。
    doneCurrent();
}

void Unit3Blending::initializeGL()
{
    //此为Qt接口:为当前上下文初始化OpenGL函数解析
    initializeOpenGLFunctions();

    //窗口颜色
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Unit3Blending::paintGL()
{
    //清除颜色缓冲区
    glClear(GL_COLOR_BUFFER_BIT);

    //开启混合，记得先绘制不透明的，再关掉深度测试绘制混合透明的
    glEnable(GL_BLEND);
    //混合方式
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //第一个红色三角
    glColor4f(1.0f,0.0f,0.0f,1.0f);
    glBegin(GL_TRIANGLES);
    glVertex3f(1.0f,1.0f,0.0f);
    glVertex3f(-1.0f,1.0f,0.0f);
    glVertex3f(-1.0f,-1.0f,0.0f);
    glEnd();

    //第二个绿色三角
    glColor4f(0.0f,1.0f,0.0f,0.5f);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.5f,-0.5f,0.0f);
    glVertex3f(0.5f,0.5f,0.0f);
    glVertex3f(-0.5f,0.5f,0.0f);
    glEnd();

    glDisable(GL_BLEND);
}

void Unit3Blending::resizeGL(int width, int height)
{
    //视口，靠左下角缩放
    glViewport(0,0,width,height);
}

void Unit3Blending::showEvent(QShowEvent *event)
{
    setFocus();
    QOpenGLWidget::showEvent(event);
}
