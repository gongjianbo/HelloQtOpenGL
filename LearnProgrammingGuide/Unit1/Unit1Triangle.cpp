#include "Unit1Triangle.h"

#include <QDebug>

Unit1Triangle::Unit1Triangle(QWidget *parent)
    : QOpenGLWidget(parent)
{

}

Unit1Triangle::~Unit1Triangle()
{
    //此为Qt接口:通过使相应的上下文成为当前上下文并在该上下文中绑定帧缓冲区对象，
    //准备为此小部件呈现OpenGL内容。在调用paintGL()之前会自动调用。
    makeCurrent();

    //删除着色器程序对象
    //void glDeleteProgram(GLuint program​);
    glDeleteProgram(shaderProgram);
    //删除顶点数组对象
    //void glDeleteVertexArrays(GLsizei n​, const GLuint *arrays​);
    //参数1为数量，参数2为顶点数组 数组
    glDeleteVertexArrays(1, vao);
    //删除命名的缓冲区对象
    //void glDeleteBuffers(GLsizei n​, const GLuint * buffers​);
    //参数1为数量，参数2为缓冲区数组
    glDeleteBuffers(1, buffer);

    //此为Qt接口:释放上下文。在大多数情况下不需要调用此函数，
    //因为小部件将确保在调用paintGL()时正确绑定和释放上下文。
    doneCurrent();
}

void Unit1Triangle::initializeGL()
{
    //此为Qt接口:为当前上下文初始化OpenGL函数解析
    initializeOpenGLFunctions();

    //生成顶点数组对象名称
    //void glGenVertexArrays(GLsizei n​, GLuint *arrays​);
    //参数1为生成名称数量，参数2为顶点数组 数组
    glGenVertexArrays(1, vao);
    //绑定一个命名的顶点数组对象
    //void glBindVertexArray(GLuint array​);
    //参数为顶点数组的名称
    glBindVertexArray(vao[0]);

    //开始绘制图形之前，我们必须先给OpenGL输入一些顶点数据
    //这里定义1个三角的三个顶点
    GLfloat  vertices[3][2] = {
        { -0.9f, -0.9f },
        {  0.9f, -0.9f },
        {  0.0f,  0.9f }
    };

    //生成缓冲区对象名称
    //void glCreateBuffers(GLsizei n,GLuint *buffers);
    //参数1为生成名称数量，参数2为缓冲区数组
    //----旧版本用glGenBuffers(GLsizei n​, GLuint * buffers​);
    //glCreateBuffers一直会创建新缓冲对象，
    //但是如果之前没有删除过的缓冲区，glGenBuffers才会创建新的缓冲区。
    glCreateBuffers(1, buffer);
    //绑定一个命名的缓冲区对象：
    //void glBindBuffer(GLenum target​, GLuint buffer​);
    //参数1缓冲对象类型，参数2缓冲对象名称
    //OpenGL有很多缓冲对象类型，顶点缓冲对象的缓冲类型是GL_ARRAY_BUFFER
    //OpenGL允许我们同时绑定多个缓冲，只要它们是不同的缓冲类型
    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    //接下来把之前定义的顶点数据复制到缓冲的内存中
    //void glBufferStorage(GLenum target,GLsizeiptr size,const void * data,GLbitfield flags);
    //参数1缓冲对象类型，参数2数据字节大小，参数3数据指针，没数据则为NULL
    //参数4指定缓冲区的数据存储的预期用途
    //----旧版本用void glBufferData(GLenum target​, GLsizeiptr size​, const GLvoid * data​, GLenum usage​);
    glBufferStorage(GL_ARRAY_BUFFER, sizeof(vertices), vertices, 0);

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
    //创建顶点着色器对象
    //GLuint glCreateShader(GLenum shaderType​);
    //参数为着色器类型
    //GL_VERTEX_SHADER：顶点着色器
    //GL_FRAGMENT_SHADER：片段着色器
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    //把着色器代码附加到着色器对象上
    //void glShaderSource(GLuint shader​, GLsizei count​, const GLchar **string​, const GLint *length​);
    //参数1着色器对象，参数2指定字符串和长度数组中的元素数
    //参数3指定指向要加载到着色器的源码字符串的指针数组（二级指针）
    //参数4指定字符串长度的数组（暂时还没明白第四个参数）
    glShaderSource(vertexShader, 1, &vertex_str, NULL);
    //编译着色器
    glCompileShader(vertexShader);

    //检测是否编译成功
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        qDebug() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << infoLog;
    }

    //创建片段着色器对象
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    //把着色器代码附加到着色器对象上，并编译
    glShaderSource(fragmentShader, 1, &fragment_str, NULL);
    glCompileShader(fragmentShader);

    //检测是否编译成功
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        qDebug() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << infoLog;
    }

    //现在两个着色器都编译了
    //接下来把两个着色器对象连接到一个用来渲染的着色器程序中

    //着色器程序对象(Shader Program Object)是多个着色器合并之后并最终链接完成的版本
    //创建程序对象
    //GLuint glCreateProgram(void​);
    //glCreateProgram创建一个空的程序对象，并返回一个非零值，该值可以被引用
    shaderProgram = glCreateProgram();

    //把之前编译的着色器附加到程序对象上
    //void glAttachShader(GLuint program​, GLuint shader​);
    //参数1程序对象，参数2待附加的着色器对象
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    //链接程序对象
    //void glLinkProgram(GLuint program​);
    //参数为程序对象
    //成功链接程序对象后，可以通过调用glUseProgram使该程序对象成为当前状态的一部分
    glLinkProgram(shaderProgram);

    //检测是否链接成功
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        qDebug() << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << infoLog;
    }

    //把着色器对象链接到程序对象以后，
    //记得删除着色器对象，我们不再需要它们了
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //安装所指定的程序对象程序作为当前再现状态的一部分
    //void glUseProgram(GLuint program​);
    glUseProgram(shaderProgram);

    //定义通用顶点属性数据的数组
    //void glVertexAttribPointer(GLuint index​, GLint size​, GLenum type​,
    //    GLboolean normalized​, GLsizei stride​, const GLvoid * pointer​);
    //参数1指定要配置的通用顶点属性的索引，对应顶点着色器中的（layout(location = 0)）
    //参数2指定顶点属性的大小，1-4
    //参数3指定数据类型
    //参数4定义我们是否希望数据被标准化，为true则数据被归一化0-1
    //参数5为字节步长，告诉我们在连续的顶点属性组之间的间隔
    //参数6表示位置数据在缓冲中起始位置的偏移量(Offset)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    //使能顶点属性数组
    //void glEnableVertexAttribArray(GLuint index​);
    //参数为顶点属性的索引
    glEnableVertexAttribArray(0);
}

void Unit1Triangle::paintGL()
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
    glBindVertexArray(vao[0]);
    //绘制三角
    //void glDrawArrays(GLenum mode​, GLint first​, GLsizei count​);
    //参数1指定要渲染的类型，如GL_TRIANGLES三角
    //参数2起始索引，参数3呈现的索引数量
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Unit1Triangle::resizeGL(int width, int height)
{
    //设置视口，缩放时是靠左下角缩放
    glViewport(0,0,width,height);
}
