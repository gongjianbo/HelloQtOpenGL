#ifndef UNIT3DEPTHTEST_H
#define UNIT3DEPTHTEST_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_0_Compatibility>

//使用深度测试绘制立体图元
//面剔除和深度测试之间的区别:
//一般面剔除是应用于一些闭合物体（比方说立方体），由于视角的缘故，我们最多能同时看到一个物体的三个面，其他三个看不到，
//那么此时，我们就可以将另外三个看不到的面剔除掉。这就是面剔除，它节省了很多系统开销。
//深度测试的话不仅用于单个物体（的两个相对面），也用于物体于物体之间。
//面剔除总是会将面丢弃（对于单个物体来说），而深度测试不会，只要Z-Value合理，它就都会渲染。
//一个明显的例子就是进入木箱内部看，开启了面剔除的木箱内部是空的，而深度测试照常渲染。
class Unit3DepthTest : public QOpenGLWidget, protected QOpenGLFunctions_4_0_Compatibility
{
    Q_OBJECT
public:
    explicit Unit3DepthTest(QWidget *parent = nullptr);
    ~Unit3DepthTest();

protected:
    //设置OpenGL资源和状态。在第一次调用resizeGL或paintGL之前被调用一次
    void initializeGL() override;
    //渲染OpenGL场景，每当需要更新小部件时使用
    void paintGL() override;
    //设置OpenGL视口、投影等，每当尺寸大小改变时调用
    void resizeGL(int width, int height) override;

    //按键事件
    void keyPressEvent(QKeyEvent *event) override;
    //设置切换显示的时候获取焦点
    void showEvent(QShowEvent *event) override;

private:
    //旋转角度
    GLfloat xRotate=5;
    GLfloat yRotate=40;
};

#endif // UNIT3DEPTHTEST_H
