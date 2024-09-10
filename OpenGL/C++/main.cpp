#include <GL/gl.h>
#include <GL/glext.h>
#include <iostream>
#include <QApplication>
#include <QOpenGLContext>
#include <QOpenGLWindow>
#include <QOpenGLWidget>
#include "ExtensionHandler.h"
#include "VertexShader.h"
#include <QOpenGLShader>
#include <QTime>
#include <QTimer>
#include <cmath>
#include <qopenglcontext.h>
#include <qopenglfunctions_4_5_core.h>
#include <qopenglshaderprogram.h>
#include "FragmentShader.h"
#include "ShaderProgram.h"
#include "inc/ExtensionHandler.h"

class OpenGLWindows: public QOpenGLWidget, public QOpenGLFunctions_4_5_Core{
  public:
    OpenGLWindows(QWidget *parent = nullptr)
    :QOpenGLWidget(parent)
    ,m_shaderProgram(new OGL::ShaderProgram())
    ,VAO(0)
    ,VBO(0){
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &OpenGLWindows::updateFrame);
        timer->start(16);
    }

    ~OpenGLWindows(){
        if(timer){
            delete timer;
            timer = nullptr;
        }
        if(m_shaderProgram){
            delete m_shaderProgram;
        }
    }

    void initializeGL() override{

        if(!initializeOpenGLFunctions()){
            qDebug()<<"QOpenGL function initialezed failed";
        }
        const GLubyte* version = glGetString(GL_VERSION);
        const GLubyte* vendor = glGetString(GL_VENDOR);
        const GLubyte* renderer = glGetString(GL_RENDERER);
        const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
        GLint major, minor;
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);
        qDebug()<<"OpenGL Version:"<<reinterpret_cast<const char*>(version);
        qDebug()<<"OpenGL Vendor:"<<reinterpret_cast<const char*>(vendor);
        qDebug()<<"OpenGL Renderer:"<<reinterpret_cast<const char*>(renderer);
        qDebug()<<"OpenGL GLSL Version:"<<reinterpret_cast<const char*>(glslVersion);
        qDebug()<<"OpenGL Version:"<<major<<"."<<minor;

        // program = new QOpenGLShaderProgram();
        // program->addShaderFromSourceFile(QOpenGLShader::Vertex, "D:/code/Graphics/OpenGL/C++/GLSL/shader.vs");
        // program->addShaderFromSourceFile(QOpenGLShader::Fragment, "D:/code/Graphics/OpenGL/C++/GLSL/shader.fs");
        // program->link();

        // 顶点着色器源码
        // 片段着色器源码
        OGL::VertexShader vertexShader = OGL::VertexShader("D:/code/Graphics/OpenGL/C++/GLSL/shader.vs");
        OGL::FragmentShader fragmentShader = OGL::FragmentShader("D:/code/Graphics/OpenGL/C++/GLSL/shader.fs");
        m_shaderProgram->create().attachShader(vertexShader).attachShader(fragmentShader).link();

        // 初始化 VAO 和 VBO
        float vertices[] = {
            // 位置        // 颜色
            -0.5f, -0.5f,  1.0f,  0.0f, 0.0f, // 左下角
             0.5f, -0.5f,  0.0f,  1.0f, 0.0f,// 右下角
             0.0f,  0.5f,  0.0f, 0.0f, 1.0f  // 顶部
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // 设置清屏颜色
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 黑色
        
    }
    void paintGL() override{
                // 获取当前时间
        QTime time = QTime::currentTime();
        int msec = time.msec();

        // 计算颜色值
        float red = (sin(msec * 0.001) + 1.0) / 2.0;
        float green = (cos(msec * 0.001) + 1.0) / 2.0;
        float blue = (sin(msec * 0.002) + 1.0) / 2.0;

        // 设置清屏颜色
        glClearColor(red, green, blue, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_shaderProgram->use();
        // program->bind();

        // 绑定 VAO
        glBindVertexArray(VAO);

        // 绘制三角形
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // 解绑 VAO
        glBindVertexArray(0);

        // program->release();

    }

    void resizeGL(int w, int h) override{
        glViewport(0, 0, w, h);
    }

private slots:
    void updateFrame() {
        makeCurrent();

        paintGL();
        this->context()->swapBuffers(this->context()->surface());

        doneCurrent();
    }

private:
    QTimer *timer;
    OGL::ShaderProgram* m_shaderProgram;

    // QT提供OpenGL Program
    QOpenGLShaderProgram* program;
    GLuint VAO, VBO;
    // OGL::OpenGLExtensionHandler* handler;

};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OpenGLWindows window;
    window.resize(800,600);
    window.show();

    return a.exec();
}