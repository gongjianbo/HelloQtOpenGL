#include "Unit4Move.h"

#include <QPainter>
#include <QVector3D>
#include <QtMath>
#include <QKeyEvent>
#include <QDebug>

Unit4Move::Unit4Move(QWidget *parent)
    : QOpenGLWidget(parent)
{
    //默认没得焦点，没法接收按键
    setFocusPolicy(Qt::StrongFocus);
}

Unit4Move::~Unit4Move()
{
    //此为Qt接口:通过使相应的上下文成为当前上下文并在该上下文中绑定帧缓冲区对象，
    //准备为此小部件呈现OpenGL内容。在调用paintGL()之前会自动调用。
    makeCurrent();

    //.. ...

    //此为Qt接口:释放上下文。在大多数情况下不需要调用此函数，
    //因为小部件将确保在调用paintGL()时正确绑定和释放上下文。
    doneCurrent();
}

void Unit4Move::initializeGL()
{
    //此为Qt接口:为当前上下文初始化OpenGL函数解析
    initializeOpenGLFunctions();

    //初始化
    //矩形分为两个三角
    vertexList=QList<QVector3D>{
    {0.5f,0.5f,0.0f},
    {-0.5f,0.5f,0.0f},
    {-0.5f,-0.5f,0.0f},
    {-0.5f,-0.5f,0.0f},
    {0.5f,-0.5f,0.0f},
    {0.5f,0.5f,0.0f} };

    //窗口清除的颜色
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Unit4Move::paintGL()
{
    //清除颜色缓冲区
    glClear(GL_COLOR_BUFFER_BIT);

    QMatrix4x4 mat;
    mat.ortho(-5,5,-5,5,-15,15);
    //先移动再旋转45度
    mat.translate(xOffset,yOffset,0);
    //mat.rotate(45,0,0,1);

    QMatrix4x4 mat2;
    mat2.rotate(45,0,0,1);

    //填充颜色
    glColor3f(0.0f,0.5f,1.0f);
    //绘制三角(坐标范围默认为[-1,1])
    glBegin(GL_TRIANGLES);
    for(const QVector3D &vertex:vertexList){
        QVector3D item=mat*mat2*vertex; //注意相乘顺序
        glVertex3f(item.x(),item.y(),item.z());
    }
    glEnd();

    //绘制文本
    QPainter painter(this);
    painter.setPen(QColor(255,255,255));
    painter.drawText(20,40,"点击获取焦点后，按方向键移动！");
}

void Unit4Move::resizeGL(int width, int height)
{
    //视口，靠左下角缩放
    glViewport(0,0,width,height);
}

void Unit4Move::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        yOffset+=0.1f;
        break;
    case Qt::Key_Down:
        yOffset-=0.1f;
        break;
    case Qt::Key_Left:
        xOffset-=0.1f;
        break;
    case Qt::Key_Right:
        xOffset+=0.1f;
        break;
    default:
        break;
    }
    update();
    QOpenGLWidget::keyPressEvent(event);
}

void Unit4Move::showEvent(QShowEvent *event)
{
    setFocus();
    QOpenGLWidget::showEvent(event);
}
