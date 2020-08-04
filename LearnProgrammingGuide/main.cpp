#include "mainwindow.h"

#include <QApplication>
#include <QSurfaceFormat>
#include <QOpenGLContext>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat fmt;
    fmt.setSamples(8);//多重采样
    if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
        //默认为2.0，设置成4.5 core
        fmt.setVersion(4, 5);
        fmt.setProfile(QSurfaceFormat::CoreProfile);
    }
    QSurfaceFormat::setDefaultFormat(fmt);

    MainWindow w;
    w.show();
    return a.exec();
}
