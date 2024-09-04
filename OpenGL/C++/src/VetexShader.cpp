#include "Shader.h"
#include "VertexShader.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include <memory>
#include <qdebug.h>
#include "ExtensionHandler.h"

namespace OGL{


OGLVertexShader::OGLVertexShader(){
}
OGLVertexShader::~OGLVertexShader(){

}


GLuint OGLVertexShader::glCreateShader(GLenum type){
    return OPENGL_EXTENSION_HANDLE->glCreateShader(type);
}

auto OGLVertexShader::Create()->OGLVertexShader&{
    m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    if(0 == m_vertexShader){
        qDebug()<<"Create vertex shader error";
    }
    return *this;
}

void OGLVertexShader::glShaderSource(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length){
    OPENGL_EXTENSION_HANDLE->glShaderSource(shader,count,string,length);
}

auto OGLVertexShader::GetSourceFrom(const GLchar *const* GLSL_source)->OGLVertexShader&{
    glShaderSource(m_vertexShader,1,GLSL_source,NULL);
    
    return *this;
}

auto OGLVertexShader::Compile()->OGLVertexShader&{
    OPENGL_EXTENSION_HANDLE->glCompileShader(m_vertexShader);
    return *this;
}

}