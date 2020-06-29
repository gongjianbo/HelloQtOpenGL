#include "Unit2Triangle.h"

#include <QSurfaceFormat>
#include <QOpenGLContext>
#include <QDebug>

Unit2Triangle::Unit2Triangle(QWidget *parent)
    : QOpenGLWidget(parent)
{
    connect(timer,&QTimer::timeout,[this]{
        //累加或减，到达极限就反转flag
        if(offsetFlag){
            offsetCount+=5;
            if(offsetCount>255){
                offsetCount=255;
                offsetFlag=!offsetFlag;
            }
        }else{
            offsetCount-=5;
            if(offsetCount<55){
                offsetCount=55;
                offsetFlag=!offsetFlag;
            }
        }
        update();
    });
    timer->start(50);
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

    //打印OpenGL信息，使用gl函数，应该是获取的系统的
    //使用了QSurfaceFormat设置gl后就不能调用这个了
    //const GLubyte * vendor = glGetString(GL_VENDOR);
    //const GLubyte * renderer = glGetString(GL_RENDERER);
    //const GLubyte * version = glGetString(GL_VERSION);
    //qDebug()<<"OpenGL实现厂商"<<(char*)vendor;
    //qDebug()<<"渲染器标识符"<<(char*)renderer;
    //qDebug()<<"OpenGL版本号"<<(char*)version;

    //QSurfaceFormat默认版本为2.0=QSurfaceFormat::defaultFormat().version()
    qDebug()<<"QSurfaceFormat::defaultFormat()"<<QSurfaceFormat::defaultFormat();

    //窗口清除的颜色
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Unit2Triangle::paintGL()
{
    //【主要部分】
    //清除颜色缓冲区
    glClear(GL_COLOR_BUFFER_BIT);

    //绘制三角(坐标范围默认为[-1,1])
    glBegin(GL_TRIANGLES);
    //三角形的三个顶点 --每个顶点一个颜色，中部分为线性插值
    glColor3f((float)(offsetCount/255.0),0.0f,0.0f);
    glVertex3f(-0.5f,-0.4f,0.0f);
    glColor3f(0.0f,(float)(offsetCount/255.0),0.0f);
    glVertex3f(0.5f,-0.4f,0.0f);
    glColor3f(0.0f,0.0f,(float)(offsetCount/255.0));
    glVertex3f( 0.0f,0.4f,0.0f );
    glEnd();
}

void Unit2Triangle::resizeGL(int width, int height)
{
    //视口，靠左下角缩放
    glViewport(0,0,width,height);
}
