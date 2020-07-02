#include "Unit3Primitives.h"

#include <QPainter>
#include <QVector3D>
#include <QtMath>
#include <QKeyEvent>
#include <QDebug>

Unit3Primitives::Unit3Primitives(QWidget *parent)
    : QOpenGLWidget(parent)
{
    //默认没得焦点，没法接收按键
    setFocusPolicy(Qt::StrongFocus);
}

Unit3Primitives::~Unit3Primitives()
{
    //此为Qt接口:通过使相应的上下文成为当前上下文并在该上下文中绑定帧缓冲区对象，
    //准备为此小部件呈现OpenGL内容。在调用paintGL()之前会自动调用。
    makeCurrent();

    //.. ...

    //此为Qt接口:释放上下文。在大多数情况下不需要调用此函数，
    //因为小部件将确保在调用paintGL()时正确绑定和释放上下文。
    doneCurrent();
}

void Unit3Primitives::initializeGL()
{
    //此为Qt接口:为当前上下文初始化OpenGL函数解析
    initializeOpenGLFunctions();

    //窗口清除的颜色
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Unit3Primitives::paintGL()
{
    //清除颜色缓冲区
    glClear(GL_COLOR_BUFFER_BIT);

    //重置当前指定的矩阵为单位矩阵，恢复坐标系
    //OpenGL是状态机，会保存之前的状态
    glLoadIdentity();
    //旋转
    glRotatef(xRotate,1.0f,0.0f,0.0f);
    glRotatef(yRotate,0.0f,1.0f,0.0f);

    switch (drawType) {
    case 0: drawPoints(); break;
    case 1: drawLines(); break;
    case 2: drawLineStrip(); break;
    case 3: drawLineLoop(); break;
    case 4: drawTriangles(); break;
    case 5: drawTriangles2(); break;
    case 6: drawTrianglesStrip(); break;
    case 7: drawTrianglesFan(); break;
    default:
        break;
    }

    //绘制文本
    QPainter painter(this);
    painter.setPen(QColor(255,255,255));
    painter.drawText(20,40,"点击获取焦点后，按空格切换图元，按方向键旋转！");
}

void Unit3Primitives::resizeGL(int width, int height)
{
    //视口，靠左下角缩放
    glViewport(0,0,width,height);
}

void Unit3Primitives::keyPressEvent(QKeyEvent *event)
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
    case Qt::Key_Space:
        //N种选择切换
        drawType++;
        drawType%=8;
        break;
    default:
        break;
    }
    //qDebug()<<event;
    update();
    QOpenGLWidget::keyPressEvent(event);
}

void Unit3Primitives::drawPoints()
{
    //点大小
    glPointSize(5.0f);
    //绘制点集合
    glBegin(GL_POINTS);
    glColor3f(0.0f,0.5f,1.0f);
    glVertex3f(-0.5f,-0.5f,0.0f);
    glVertex3f(0.5f,-0.5f,0.0f);
    glVertex3f(0.5f,0.5f,0.0f );
    glVertex3f(-0.5f,0.5f,0.0f );
    glEnd();
    glPointSize(1.0f);
}

void Unit3Primitives::drawLines()
{
    //线宽
    glLineWidth(2.0f);
    //绘制线段集合
    glBegin(GL_LINES);
    glColor3f(0.0f,0.5f,1.0f);
    glVertex3f(-0.5f,-0.5f,0.0f);
    glVertex3f(0.5f,-0.5f,0.0f);
    glVertex3f(0.5f,0.5f,0.0f );
    glVertex3f(-0.5f,0.5f,0.0f );
    glEnd();
    glLineWidth(1.0f);
}

void Unit3Primitives::drawLineLoop()
{
    //线宽
    glLineWidth(2.0f);
    //绘制线-链接头尾
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f,0.5f,1.0f);
    glVertex3f(-0.5f,-0.5f,0.0f);
    glVertex3f(0.5f,-0.5f,0.0f);
    glVertex3f(0.5f,0.5f,0.0f );
    glVertex3f(-0.5f,0.5f,0.0f );
    glEnd();
    glLineWidth(1.0f);
}

void Unit3Primitives::drawLineStrip()
{
    //线宽
    glLineWidth(2.0f);
    //绘制线-没链接头尾
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f,0.5f,1.0f);
    glVertex3f(-0.5f,-0.5f,0.0f);
    glVertex3f(0.5f,-0.5f,0.0f);
    glVertex3f(0.5f,0.5f,0.0f );
    glVertex3f(-0.5f,0.5f,0.0f );
    glEnd();
    glLineWidth(1.0f);
}

void Unit3Primitives::drawTriangles()
{
    //绘制三角
    glBegin(GL_TRIANGLES);

    //矩形分为两个三角
    glColor3f(0.0f,0.5f,1.0f);
    glVertex3f(0.5f,0.5f,0.0f);
    glVertex3f(-0.5f,0.5f,0.0f);
    glVertex3f(-0.5f,-0.5f,0.0f);

    glColor3f(1.0f,0.5f,0.0f);
    glVertex3f(-0.5f,-0.5f,0.0f);
    glVertex3f(0.5f,-0.5f,0.0f );
    glVertex3f(0.5f,0.5f,0.0f );
    glEnd();
}

void Unit3Primitives::drawTriangles2()
{
    //三角形组成的金字塔
    QList<QVector3D> data_list={
        {0.0f,0.5f,0.0f},
        {-0.4f,-0.4f,0.3f},
        {0.4f,-0.4f,0.3f},

        {0.0f,0.5f,0.0f},
        {0.0f,-0.4f,-0.3f},
        {-0.4f,-0.4f,0.3f},

        {0.0f,0.5f,0.0f},
        {0.4f,-0.4f,0.3f},
        {0.0f,-0.4f,-0.3f}
    };
    //绘制
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f,0.5f,1.0f);
    for(const QVector3D &item:data_list)
    {
        glVertex3f(item.x(),item.y(),item.z());
    }
    glEnd();

    //下面这部分内容是从Demo复制过来的，但是效果不一样，
    //这里框线穿透了，但是Demo是有正反面的
    // Draw black outline
    glPolygonOffset(-1.0f, -1.0f);      // Shift depth values
    glEnable(GL_POLYGON_OFFSET_LINE);

    // Draw lines antialiased
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //框线模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //绘制
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f,1.0f,0.0f);
    for(const QVector3D &item:data_list)
    {
        glVertex3f(item.x(),item.y(),item.z());
    }
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_POLYGON_OFFSET_LINE);
    glDisable(GL_BLEND);
    glDisable(GL_LINE_SMOOTH);
}

void Unit3Primitives::drawTrianglesStrip()
{
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

    // Draw black outline
    glPolygonOffset(-1.0f, -1.0f);      // Shift depth values
    glEnable(GL_POLYGON_OFFSET_LINE);

    // Draw lines antialiased
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //框线模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //绘制
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1.0f,1.0f,0.0f);
    for(const QVector3D &item:data_list)
    {
        glVertex3f(item.x(),item.y(),item.z());
    }
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_POLYGON_OFFSET_LINE);
    glDisable(GL_BLEND);
    glDisable(GL_LINE_SMOOTH);
}

void Unit3Primitives::drawTrianglesFan()
{
    //扇形，围绕中心点（第一个点）产生的三角
    QList<QVector3D> data_list;
    // For a Triangle fan, just a 6 sided hex. Raise the center up a bit
    data_list.push_back({0.0f,0.0f,0.0f}); //原点
    GLfloat the_radius = 0.5f; //半径 0.5f
    for(GLfloat angle = 0; angle < (2.0f*M_PI); angle += (float)(2.0f*M_PI) / 6.0f) {
        data_list.push_back({(float)qCos(angle)* the_radius,
                             (float)qSin(angle) * the_radius,
                             -0.5f});
    }
    //绘制
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f,0.5f,1.0f);
    for(const QVector3D &item:data_list)
    {
        glVertex3f(item.x(),item.y(),item.z());
    }
    glEnd();

    // Draw black outline
    glPolygonOffset(-1.0f, -1.0f);      // Shift depth values
    glEnable(GL_POLYGON_OFFSET_LINE);

    // Draw lines antialiased
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //框线模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //绘制
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f,1.0f,0.0f);
    for(const QVector3D &item:data_list)
    {
        glVertex3f(item.x(),item.y(),item.z());
    }
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_POLYGON_OFFSET_LINE);
    glDisable(GL_BLEND);
    glDisable(GL_LINE_SMOOTH);
}
