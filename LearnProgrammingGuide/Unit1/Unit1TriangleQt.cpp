#include "Unit1TriangleQt.h"

#include <QDebug>

Unit1TriangleQt::Unit1TriangleQt(QWidget *parent)
    : QOpenGLWidget(parent)
{

}

Unit1TriangleQt::~Unit1TriangleQt()
{
    //此为Qt接口:通过使相应的上下文成为当前上下文并在该上下文中绑定帧缓冲区对象，
    //准备为此小部件呈现OpenGL内容。在调用paintGL()之前会自动调用。
    makeCurrent();

    //删除顶点数组对象
    vao.destroy();
    //删除命名的缓冲区对象
    vbo.destroy();

    //此为Qt接口:释放上下文。在大多数情况下不需要调用此函数，
    //因为小部件将确保在调用paintGL()时正确绑定和释放上下文。
    doneCurrent();
}

void Unit1TriangleQt::initializeGL()
{
    //此为Qt接口:为当前上下文初始化OpenGL函数解析
    initializeOpenGLFunctions();

    //开始绘制图形之前，我们必须先给OpenGL输入一些顶点数据
    //这里定义1个三角的三个顶点
    GLfloat  vertices[3][2] = {
        { -0.9f, -0.9f },
        {  0.9f, -0.9f },
        {  0.0f,  0.9f }
    };

    //生成顶点数组对象
    vao.create();
    vao.bind();

    //生成顶点缓冲对象
    vbo=QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbo.create();
    vbo.bind();
    vbo.allocate(vertices,sizeof(vertices));

    //着色器代码
    //in输入，out输出,uniform从cpu向gpu发送
    //这里有个疑问，为什么传进来是vec2，却可以用vec4接收
    const char *vertex_str=R"(#version 450 core
                           layout (location = 0) in vec4 pos;
                           void main() {
                           gl_Position = pos;
                           })";
    //颜色选用纯正的原谅绿
    const char *fragment_str=R"(#version 450 core
                             out vec4 outColor;
                             void main() {
                             outColor = vec4(0.0,1.0,0.0,1.0);
                             })";
    //将source编译为指定类型的着色器，并添加到此着色器程序
    if(!shaderProgram.addCacheableShaderFromSourceCode(
                QOpenGLShader::Vertex,vertex_str)){
        qDebug()<<"compiler vertex error"<<shaderProgram.log();
    }
    if(!shaderProgram.addCacheableShaderFromSourceCode(
                QOpenGLShader::Fragment,fragment_str)){
        qDebug()<<"compiler fragment error"<<shaderProgram.log();
    }
    //将添加到该程序的着色器链接在一起。
    if(!shaderProgram.link()){
        qDebug()<<"link shaderprogram error"<<shaderProgram.log();
    }


    //定义通用顶点属性数据的数组
    //void setAttributeBuffer(int location, GLenum type, int offset, int tupleSize, int stride = 0);
    shaderProgram.setAttributeBuffer(0, GL_FLOAT, 0, 2, 0);
    //使能顶点属性数组
    shaderProgram.enableAttributeArray(0);
}

void Unit1TriangleQt::paintGL()
{
    //OpenGL清理缓存的两种方法
    //1.初始化时，调用glClearColor()、glClearDepth()及glClearStencil()
    //分别设置清空后颜色缓存、深度缓存和模板缓存中的默认值；
    //2.在每一帧渲染前，调用glClear()并传入
    //GL_COLOR_BUFFER_BIT、GL_DEPTH_BUFFER_BIT、GL_STENCIL_BUFFER_BIT
    //或它们的位组合进行对应缓存的清空操作。
    //OpenGL 3.0中，新增了接口glClearBuffer*()
    static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    //void glClearBufferfv(GLenum buffer,GLint drawbuffer, const GLfloat* value);
    //buffer可以传入GL_COLOR、GL_DEPTH或GL_STENCIL，以指明我们要清空哪种缓存
    //drawbuffer用于多输出缓存的情况
    //value指明了清空后的默认值
    glClearBufferfv(GL_COLOR, 0, black);

    //因为OpenGL使用状态机模式，所以在初始化设置的东西这里可以不用再次设置，除非要切换/修改

    //激活vao
    vao.bind();
    shaderProgram.bind();
    //绘制三角
    //void glDrawArrays(GLenum mode​, GLint first​, GLsizei count​);
    //参数1指定要渲染的类型，如GL_TRIANGLES三角
    //参数2起始索引，参数3呈现的索引数量
    glDrawArrays(GL_TRIANGLES, 0, 3);

    shaderProgram.release();
    vao.release();
}

void Unit1TriangleQt::resizeGL(int width, int height)
{
    //设置视口，缩放时是靠左下角缩放
    glViewport(0,0,width,height);
}
