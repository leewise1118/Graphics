#include "Shader.h"
#include "FragmentShader.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include <memory>
#include <qdebug.h>
#include "ExtensionHandler.h"
#include <fstream>
#include <sstream>

namespace OGL{


FragmentShader::FragmentShader(const GLchar* fragmentPath){
    create().readGLSLandCompile(fragmentPath);
}
FragmentShader::~FragmentShader(){
    if(!deleteShader()){
        qDebug()<<"delete fragment shader error";
    }
}


GLuint FragmentShader::glCreateShader(GLenum type){
    return OPENGL_EXTENSION_HANDLE->glCreateShader(type);
}

auto FragmentShader::create()->FragmentShader&{
    m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if(0 == m_fragmentShader){
        qDebug()<<"Create fragment shader error";
    }
    return *this;
}

void FragmentShader::glShaderSource(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length){
    OPENGL_EXTENSION_HANDLE->glShaderSource(shader,count,string,length);
}

auto FragmentShader::readGLSLandCompile(const GLchar* fragmentPath)->void{
if(m_fragmentShader == 0){
        qDebug()<<"fragment shader is not created";
        return ;
    }
     // 1. 从文件路径中获取顶点/片段着色器
    std::string fragmentCode;
    std::ifstream vShaderFile;
    // 保证ifstream对象可以抛出异常：
    vShaderFile.exceptions(std::ifstream::badbit);
    try 
    {
        // 打开文件
        vShaderFile.open(fragmentPath);
        std::stringstream vShaderStream;
        // 读取文件的缓冲内容到流中
        vShaderStream << vShaderFile.rdbuf();
        // 关闭文件
        vShaderFile.close();
        // 转换流至GLchar数组
        fragmentCode = vShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const GLchar* vShaderCode = fragmentCode.c_str();

    glShaderSource(m_fragmentShader,1,&vShaderCode,NULL);
    OPENGL_EXTENSION_HANDLE->glCompileShader(m_fragmentShader);

    // 打印编译错误（如果有的话）
    GLint success;
    GLchar infoLog[512];
    OPENGL_EXTENSION_HANDLE->glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        OPENGL_EXTENSION_HANDLE->glGetShaderInfoLog(m_fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::fragment::COMPILATION_FAILED\n" << infoLog << std::endl;
    };
}

auto FragmentShader::deleteShader()->bool{
    if(m_fragmentShader != 0){
        OPENGL_EXTENSION_HANDLE->glDeleteShader(m_fragmentShader);
        return true;
    }
    return false;
}


}