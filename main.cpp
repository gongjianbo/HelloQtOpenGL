#include "mainwindow.h"

#include <QApplication>
#include <QSurfaceFormat>
#include <QOpenGLContext>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if 0
    QSurfaceFormat fmt;
    //fmt.setSamples(8);//多重采样
    // Request OpenGL 4.0 or OpenGL ES 3.0.
    if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
        qDebug("Requesting GL4.0 context");
        //默认为2.0
        fmt.setVersion(4, 0);
        //core or compatibility
        fmt.setProfile(QSurfaceFormat::CompatibilityProfile);
    } else {
        qDebug("Requesting ES3.0 context");
        fmt.setVersion(3, 0);
    }
    //为什么设置之后固定管线画不出来
    QSurfaceFormat::setDefaultFormat(fmt);
#endif
    //为了使用多重采样，Qt还要设置setSamples
    QSurfaceFormat fmt=QSurfaceFormat::defaultFormat();
    //多重采样
    fmt.setSamples(8);
    QSurfaceFormat::setDefaultFormat(fmt);

    MainWindow w;
    w.show();
    return a.exec();
}
