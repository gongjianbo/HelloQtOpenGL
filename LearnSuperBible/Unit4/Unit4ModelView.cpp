#include "Unit4ModelView.h"

#include <QPainter>
#include <QVector3D>
#include <QMatrix4x4>

#include <QtMath>
#include <QTimer>
#include <QDebug>

Unit4ModelView::Unit4ModelView(QWidget *parent)
    : QOpenGLWidget(parent)
{
    //默认没得焦点，没法接收按键
    setFocusPolicy(Qt::StrongFocus);

    QTimer *timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,[this](){
        yRotate+=5;
        update();
    });
    timer->start(100);
}

Unit4ModelView::~Unit4ModelView()
{
    //此为Qt接口:通过使相应的上下文成为当前上下文并在该上下文中绑定帧缓冲区对象，
    //准备为此小部件呈现OpenGL内容。在调用paintGL()之前会自动调用。
    makeCurrent();

    //.. ...

    //此为Qt接口:释放上下文。在大多数情况下不需要调用此函数，
    //因为小部件将确保在调用paintGL()时正确绑定和释放上下文。
    doneCurrent();
}

void Unit4ModelView::initializeGL()
{
    //此为Qt接口:为当前上下文初始化OpenGL函数解析
    initializeOpenGLFunctions();

    //窗口清除的颜色
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //深度缓冲区
    glEnable(GL_DEPTH_TEST);
    //框线模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Unit4ModelView::paintGL()
{
    //清除缓冲区
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    //将当前矩阵置为单位矩阵
    glLoadIdentity();
    //绕y轴旋转
    glRotated(yRotate,0,1,0);
    //三角带
    //
    //  *0 -  *2 - *4
    //    \  / \  /
    //     *1 - *3
    //
    //0-1-2 then 2-1-3 then 2-3-4
    QList<QVector3D> data_list;
    // For triangle strips, a little ring or cylinder segment
    GLfloat the_radius = 0.5f; //半径 0.5f
    GLfloat the_height = 0.2f; //z轴范围 +-0.2f
    for(GLfloat angle = 0.0f; angle <= (2.0f*M_PI); angle += 0.3f)
    {
        GLfloat x = the_radius * qSin(angle);
        GLfloat y = the_radius * qCos(angle);

        // Specify the point and move the Z value up a little
        data_list.push_back({x,y,-the_height});
        data_list.push_back({x,y,the_height});
    }
    // Close up the loop
    QVector3D first=data_list.at(0);
    first.setZ(-the_height);
    QVector3D second=data_list.at(1);
    second.setZ(the_height);
    data_list.push_back(first);
    data_list.push_back(second);
    //绘制
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0.0f,0.5f,1.0f);
    for(const QVector3D &item:data_list)
    {
        glVertex3f(item.x(),item.y(),item.z());
    }
    glEnd();
}

void Unit4ModelView::resizeGL(int width, int height)
{
    //视口，靠左下角缩放
    glViewport(0,0,width,height);
    //当前矩阵位投影矩阵
    glMatrixMode(GL_PROJECTION);
    //将当前矩阵置为单位矩阵
    glLoadIdentity();
    //透视投影
    MyPerspective(45.0, (double)width/height, 1.0, 1000.0);
    //观察点后退
    glTranslatef(0,0,-3);
    //切换当前矩阵为模型矩阵
    glMatrixMode(GL_MODELVIEW);
}

void Unit4ModelView::showEvent(QShowEvent *event)
{
    QOpenGLWidget::showEvent(event);
    setFocus();
}

void Unit4ModelView::MyPerspective(double fovy, double aspect, double zNear, double zFar)
{
    double xmin, xmax, ymin, ymax;
    ymax = zNear * tan(fovy * 3.14159265 / 360.0);
    ymin = -ymax;
    xmin = ymin * aspect;
    xmax = ymax * aspect;

    glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
}
