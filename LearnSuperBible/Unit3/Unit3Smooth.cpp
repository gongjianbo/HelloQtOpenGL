#include "Unit3Smooth.h"

#include <QKeyEvent>
#include <QPainter>
#include <QVector3D>
#include <QtMath>
#include <QDebug>

Unit3Smooth::Unit3Smooth(QWidget *parent)
    : QOpenGLWidget(parent)
{
    //默认没得焦点，没法接收按键
    setFocusPolicy(Qt::StrongFocus);
}

Unit3Smooth::~Unit3Smooth()
{
    //此为Qt接口:通过使相应的上下文成为当前上下文并在该上下文中绑定帧缓冲区对象，
    //准备为此小部件呈现OpenGL内容。在调用paintGL()之前会自动调用。
    makeCurrent();

    //.. ...

    //此为Qt接口:释放上下文。在大多数情况下不需要调用此函数，
    //因为小部件将确保在调用paintGL()时正确绑定和释放上下文。
    doneCurrent();
}

void Unit3Smooth::initializeGL()
{
    //此为Qt接口:为当前上下文初始化OpenGL函数解析
    initializeOpenGLFunctions();

    //窗口颜色
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Unit3Smooth::paintGL()
{
    //清除颜色缓冲区
    glClear(GL_COLOR_BUFFER_BIT);
    //（窗口初始化的时候貌似被多重采样设置影响了）
    glDisable(GL_MULTISAMPLE);

    if(smoothOn){
        //开启混合
        glEnable(GL_BLEND);
        //混合方式
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //启用混合并设置混合方式后，
        //可以调用glEnable对点、线、多边形进行抗锯齿处理
        //对于多边形，重叠的图形需要特殊处理
        glEnable(GL_POINT_SMOOTH);
        //GL_POINT_SMOOTH_HINT：指定反走样点的采样质量，如果应用较大的滤波函数，
        //GL_NICEST在光栅化期间可以生成更多的像素段。

        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
        glEnable(GL_LINE_SMOOTH);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
        glEnable(GL_POLYGON_SMOOTH);
        glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    }

    glColor3f(1.0f,1.0f,1.0f);//白色

    glPointSize(10.0f);
    //画点
    glBegin(GL_POINTS);
    glVertex2f(0.5f,0.5f);
    glVertex2f(-0.2f,0.5f);
    glEnd();

    glLineWidth(5.0f);
    //画折线
    glBegin(GL_LINE_STRIP); //GL_LINES是多个线段
    glVertex2f(-1.0f,0.0f);
    glVertex2f(-0.5f,-0.5f);
    glVertex2f(0.0f,0.0f);
    glVertex2f(0.5f,-0.5f);
    glVertex2f(0.9f,0.9f);
    glEnd();
    //画多边形
    QList<QVector3D> data_list;
    data_list.push_back({-0.5f,0.5f,0.0f}); //扇形要用原点
    GLfloat the_radius = 0.2f; //半径 0.5f
    for(GLfloat angle = 0; angle < (2.0f*M_PI); angle += (float)(2.0f*M_PI) / 24.0f) {
        data_list.push_back({-0.5f+(float)qCos(angle)* the_radius,
                             0.5f+(float)qSin(angle) * the_radius,
                             0.0f});
    }
    //绘制（貌似画扇形/多边形抗锯齿都没啥效果）
    glBegin(GL_TRIANGLE_FAN);//GL_POLYGON
    for(const QVector3D &item:data_list)
    {
        glVertex3f(item.x(),item.y(),item.z());
    }
    glEnd();

    if(smoothOn){
        glDisable(GL_POINT_SMOOTH);
        glDisable(GL_LINE_SMOOTH);
        glDisable(GL_POLYGON_SMOOTH);
        glDisable(GL_BLEND);
    }
    glLineWidth(1.0f);
    glPointSize(1.0f);

    //绘制文本
    QPainter painter(this);
    painter.setPen(QColor(255,255,255));
    painter.drawText(20,40,"点击获取焦点后，按空格切换抗锯齿！");
    painter.drawText(20,70,(smoothOn?"Smooth:On":"Smooth:Off"));
}

void Unit3Smooth::resizeGL(int width, int height)
{
    //视口，靠左下角缩放
    glViewport(0,0,width,height);
}

void Unit3Smooth::showEvent(QShowEvent *event)
{
    setFocus();
    QOpenGLWidget::showEvent(event);
}

void Unit3Smooth::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    break;
    case Qt::Key_Space:
        //切换
        smoothOn=!smoothOn;
        break;
    default:
        break;
    }
    update();
    QOpenGLWidget::keyPressEvent(event);
}
