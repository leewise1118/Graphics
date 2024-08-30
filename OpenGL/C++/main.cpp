#include <GL/gl.h>
#include <iostream>
#include <QApplication>
#include <QOpenGLContext>
#include <QOpenGLWindow>
#include <QOpenGLWidget>
#include "ExtensionHandler.h"
#include <QOpenGLShader>
#include <QTime>
#include <QTimer>
#include <cmath>
#include <qopenglcontext.h>
#include <qopenglfunctions_4_5_core.h>

class OpenGLWindows: public QOpenGLWidget, public QOpenGLFunctions_4_5_Core{
  public:
    OpenGLWindows(QWidget *parent = nullptr)
    :QOpenGLWidget(parent)
    ,handler(new OGL::OpenGLExtensionHandler()){
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &OpenGLWindows::updateFrame);
        timer->start(16);
    }
    ~OpenGLWindows(){
    }

    void initializeGL() override{
        initializeOpenGLFunctions();
        // 顶点着色器源码
        const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        void main(){
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
        )";

        // 片段着色器源码
        const char* fragmentShaderSource = R"(
        #version 420 core
        in vec3 fragColor;
        out vec4 color;
        void main() {
            color = vec4(fragColor, 1.0);
        }
        )";

        // 初始化着色器程序
        shaderProgram = new QOpenGLShaderProgram();
        shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
        shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
        shaderProgram->link();

        // 初始化 VAO 和 VBO
        float vertices[] = {
            // 位置        // 颜色
            -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // 左下角
             0.5f, -0.5f,  0.0f, 1.0f, 0.0f, // 右下角
             0.0f,  0.5f,  0.0f, 0.0f, 1.0f  // 顶部
        };

        handler->glGenVertexArrays(1, &VAO);
        handler->glGenBuffers(1, &VBO);

        handler->glBindVertexArray(VAO);

        handler->glBindBuffer(GL_ARRAY_BUFFER, VBO);
        handler->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        handler->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        handler->glEnableVertexAttribArray(0);
        handler->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
        handler->glEnableVertexAttribArray(1);

        handler->glBindBuffer(GL_ARRAY_BUFFER, 0);
        handler->glBindVertexArray(0);

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

        // 使用着色器程序
        shaderProgram->bind();

        // 绑定 VAO
        glBindVertexArray(VAO);

        // 绘制三角形
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // 解绑 VAO
        glBindVertexArray(0);

        // 释放着色器程序
        shaderProgram->release();
    }

    void resizeGL(int w, int h) override{
        glViewport(0, 0, w, h);
    }

private slots:
    void updateFrame() {
        // 请求重新绘制窗口
        // if (!isExposed())
        //     return;
        update();
    }

private:
    QTimer *timer;
    QOpenGLShaderProgram* shaderProgram;
    GLuint VAO, VBO;
    OGL::OpenGLExtensionHandler* handler;

};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OpenGLWindows window;
    window.resize(800,600);
    window.show();

    return a.exec();
}