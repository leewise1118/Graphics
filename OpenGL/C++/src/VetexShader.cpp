#include "Shader.h"
#include "VertexShader.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include <memory>
#include <qdebug.h>
#include "ExtensionHandler.h"
#include <fstream>
#include <sstream>

namespace OGL{


VertexShader::VertexShader(const GLchar* vertexPath){
    create().readGLSLandCompile(vertexPath);
}
VertexShader::~VertexShader(){
    if(!deleteShader()){
        qDebug()<<"delete Vertex shader error";
    }
}


GLuint VertexShader::glCreateShader(GLenum type){
    return OPENGL_EXTENSION_HANDLE->glCreateShader(type);
}

auto VertexShader::create()->VertexShader&{
    m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    if(0 == m_vertexShader){
        qDebug()<<"Create vertex shader error";
    }
    return *this;
}

void VertexShader::glShaderSource(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length){
    OPENGL_EXTENSION_HANDLE->glShaderSource(shader,count,string,length);
}

auto VertexShader::readGLSLandCompile(const GLchar* vertexPath)->void{
    if(m_vertexShader == 0){
        qDebug()<<"Vertex shader is not created";
        return ;
    }
     // 1. 从文件路径中获取顶点/片段着色器
    std::string vertexCode;
    std::ifstream vShaderFile;
    // 保证ifstream对象可以抛出异常：
    vShaderFile.exceptions(std::ifstream::badbit);
    try 
    {
        // 打开文件
        vShaderFile.open(vertexPath);
        std::stringstream vShaderStream;
        // 读取文件的缓冲内容到流中
        vShaderStream << vShaderFile.rdbuf();
        // 关闭文件
        vShaderFile.close();
        // 转换流至GLchar数组
        vertexCode = vShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const GLchar* vShaderCode = vertexCode.c_str();

    glShaderSource(m_vertexShader,1,&vShaderCode,NULL);
    OPENGL_EXTENSION_HANDLE->glCompileShader(m_vertexShader);

    // 打印编译错误（如果有的话）
    GLint success;
    GLchar infoLog[512];
    OPENGL_EXTENSION_HANDLE->glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        OPENGL_EXTENSION_HANDLE->glGetShaderInfoLog(m_vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };
}


auto VertexShader::deleteShader()->bool{
    if(m_vertexShader != 0){
        OPENGL_EXTENSION_HANDLE->glDeleteShader(m_vertexShader);
        return true;
    }
    return false;
}

}