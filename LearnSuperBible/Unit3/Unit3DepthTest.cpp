#include "Unit3DepthTest.h"

#include <QPainter>
#include <QVector3D>
#include <QtMath>
#include <QKeyEvent>
#include <QDebug>

Unit3DepthTest::Unit3DepthTest(QWidget *parent)
    : QOpenGLWidget(parent)
{
    //默认没得焦点，没法接收按键
    setFocusPolicy(Qt::StrongFocus);
}

Unit3DepthTest::~Unit3DepthTest()
{
    //此为Qt接口:通过使相应的上下文成为当前上下文并在该上下文中绑定帧缓冲区对象，
    //准备为此小部件呈现OpenGL内容。在调用paintGL()之前会自动调用。
    makeCurrent();

    //.. ...

    //此为Qt接口:释放上下文。在大多数情况下不需要调用此函数，
    //因为小部件将确保在调用paintGL()时正确绑定和释放上下文。
    doneCurrent();
}

void Unit3DepthTest::initializeGL()
{
    //此为Qt接口:为当前上下文初始化OpenGL函数解析
    initializeOpenGLFunctions();

    //窗口清除的颜色
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Unit3DepthTest::paintGL()
{
    //清除颜色缓冲区和深度缓冲区
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    //设置面剔除模式，可以是BACK、FRONT、FRONT_AND_BACK
    //glCullFace(GL_BACK); //剔除背面
    //设置表面顺序
    //glFrontFace(GL_CW);//默认CCW逆时针，这里使用CW顺时针
    //开始面剔除，因为表面是纯色的，所以就不剔除了
    //glEnable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);//开启深度测试

    //放到resize里去了
    //当前矩阵位投影矩阵
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity(); //单位矩阵
    //设置为正交投影
    //glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far)
    //glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);

    //当前矩阵为模型矩阵
    glMatrixMode(GL_MODELVIEW);
    //重置当前指定的矩阵为单位矩阵，恢复坐标系
    //OpenGL是状态机，会保存之前的状态
    glLoadIdentity();
    //旋转
    glRotatef(xRotate,1.0f,0.0f,0.0f);
    glRotatef(yRotate,0.0f,1.0f,0.0f);

    //三角形组成的金字塔
    //            0(0,0.4,0)
    //          . . .
    //         .  .  .
    //        .   .   .
    //       .    3(0.0,-0.4,-0.6)
    //      .   .   .   .
    //     . .         . .
    //   1 . . . . . . . . 2
    // (-0.5,-0.4,0.4)  (0.5,-0.4,0.4)
    //顶点和索引
    QList<QVector3D> vertex{
        {0.0f,0.4f,0.0f},
        {-0.5f,-0.4f,0.4f},
        {0.5f,-0.4f,0.4f},
        {0.0f,-0.4f,-0.6f}
    };
    QList<int> element{
        0,2,1,
        0,1,3,
        0,3,2,
        1,2,3
    };
    //绘制图元的表面
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f,0.5f,0.0f);
    for(int index:element)
    {
        const QVector3D &point=vertex.at(index);
        glVertex3f(point.x(),point.y(),point.z());
    }
    glEnd();

    //框线模式来描边
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //绘制线
    glBegin(GL_LINES);
    glColor3f(1.0f,1.0f,1.0f);
    for(int index:element)
    {
        const QVector3D &point=vertex.at(index);
        glVertex3f(point.x(),point.y(),point.z());
    }
    glEnd();
    //恢复设置
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //绘制文本
    QPainter painter(this);
    painter.setPen(QColor(255,255,255));
    painter.drawText(20,40,"点击获取焦点后，按方向键旋转！");
}

void Unit3DepthTest::resizeGL(int width, int height)
{
    //视口，靠左下角缩放
    glViewport(0,0,width,height);

    //当前矩阵位投影矩阵
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); //单位矩阵
    //设置为正交投影
    //貌似开了深度测试，没设置投影的话，显示有点问题，面剔除就是正常的
    //glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far)
    glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0); //near和far取反
}

void Unit3DepthTest::keyPressEvent(QKeyEvent *event)
{
    //左右转围绕的是y轴，上下转围绕的是x轴
    switch (event->key()) {
    case Qt::Key_Up:
        xRotate+=5;
        break;
    case Qt::Key_Down:
        xRotate-=5;
        break;
    case Qt::Key_Left:
        yRotate+=5;
        break;
    case Qt::Key_Right:
        yRotate-=5;
        break;
    default:
        break;
    }
    update();
    QOpenGLWidget::keyPressEvent(event);
}

void Unit3DepthTest::showEvent(QShowEvent *event)
{
    setFocus();
    QOpenGLWidget::showEvent(event);
}
