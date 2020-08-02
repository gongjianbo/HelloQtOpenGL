#include "Unit3MultiSample.h"

#include <QKeyEvent>
#include <QPainter>
#include <QVector3D>
#include <QtMath>
#include <QDebug>

Unit3MultiSample::Unit3MultiSample(QWidget *parent)
    : QOpenGLWidget(parent)
{
    //默认没得焦点，没法接收按键
    setFocusPolicy(Qt::StrongFocus);
}

Unit3MultiSample::~Unit3MultiSample()
{
    //此为Qt接口:通过使相应的上下文成为当前上下文并在该上下文中绑定帧缓冲区对象，
    //准备为此小部件呈现OpenGL内容。在调用paintGL()之前会自动调用。
    makeCurrent();

    //.. ...

    //此为Qt接口:释放上下文。在大多数情况下不需要调用此函数，
    //因为小部件将确保在调用paintGL()时正确绑定和释放上下文。
    doneCurrent();
}

void Unit3MultiSample::initializeGL()
{
    //此为Qt接口:为当前上下文初始化OpenGL函数解析
    initializeOpenGLFunctions();

    //GLint buf,sbuf;
    //glGetIntegerv(GL_SAMPLE_BUFFERS,&buf);
    //qDebug()<<"number of sample buffers is"<<buf;
    //glGetIntegerv(GL_SAMPLES,&sbuf);
    //qDebug()<<"number of samples is"<<sbuf;

    //窗口颜色
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Unit3MultiSample::paintGL()
{
    //清除颜色缓冲区
    glClear(GL_COLOR_BUFFER_BIT);

    if(sampleOn){
        //开启多重采样
        //如果没有多重采样缓冲区，GL_MULTISAMPLE当作被禁止的
        glEnable(GL_MULTISAMPLE);

        //多重采样缓冲区默认使用片段的RGB值，不包含透明度，需要单独设置
        //三者之一
        //GL_SAMPLE_ALPHA_TO_COVERAGE
        //GL_SAMPLE_ALPHA_TO_ONE
        //GL_SAMPLE_COVERAGE
        glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
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

    if(sampleOn){
        glDisable(GL_MULTISAMPLE);
        glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
    }
    glLineWidth(1.0f);
    glPointSize(1.0f);

    //绘制文本
    QPainter painter(this);
    painter.setPen(QColor(255,255,255));
    painter.drawText(20,40,"点击获取焦点后，按空格切换多重采样！");
    painter.drawText(20,70,(sampleOn?"Sample:On":"Sample:Off"));
}

void Unit3MultiSample::resizeGL(int width, int height)
{
    //视口，靠左下角缩放
    glViewport(0,0,width,height);
}

void Unit3MultiSample::showEvent(QShowEvent *event)
{
    setFocus();
    QOpenGLWidget::showEvent(event);
}

void Unit3MultiSample::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    break;
    case Qt::Key_Space:
        //切换
        sampleOn=!sampleOn;
        break;
    default:
        break;
    }
    update();
    QOpenGLWidget::keyPressEvent(event);
}
