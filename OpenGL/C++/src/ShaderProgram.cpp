#include "ShaderProgram.h"
#include "VertexShader.h"
#include <qdebug.h>

namespace OGL{
ShaderProgram::ShaderProgram()
: m_shaderProgram(0){
    // create();
}
ShaderProgram::~ShaderProgram(){

}

auto ShaderProgram::create()->ShaderProgram&{
   m_shaderProgram = OPENGL_EXTENSION_HANDLE->glCreateProgram();
   return *this;
}

auto ShaderProgram::attachShader(VertexShader& vs)->ShaderProgram&{
    // TODO: 处理附着对象的顺序，如果顺序出错，则报错
    OPENGL_EXTENSION_HANDLE->glAttachShader(m_shaderProgram, vs.getShader());
    return *this;
}

auto ShaderProgram::attachShader(FragmentShader& fs)->ShaderProgram&{
    // TODO: 处理附着对象的顺序，如果顺序出错，则报错
    OPENGL_EXTENSION_HANDLE->glAttachShader(m_shaderProgram, fs.getShader());
    return *this;
}

auto ShaderProgram::link()->bool{
    if(m_shaderProgram == 0){
        qDebug()<<"shader program is not created";
        return false;
    }
    OPENGL_EXTENSION_HANDLE->glLinkProgram(m_shaderProgram);

    GLint success;
    GLchar infoLog[512];
    OPENGL_EXTENSION_HANDLE->glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        OPENGL_EXTENSION_HANDLE->glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    return true;
}

auto ShaderProgram::use()->void{
    OPENGL_EXTENSION_HANDLE->glUseProgram(m_shaderProgram);
}

}