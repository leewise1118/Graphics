#include "VertexShader.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include <memory>
#include "ExtensionHandler.h"

namespace OGL{


OpenGLVertexShader::OpenGLVertexShader(){
    createShader();
}
OpenGLVertexShader::~OpenGLVertexShader(){

}


auto OpenGLVertexShader::createShader()->Result<self,VertexShaderError>{
    m_vertexShader = OPENGL_EXTENSION_HANDLE->glCreateShader(GL_VERTEX_SHADER);
    if(0 == m_vertexShader){
        return Err(VertexShaderError::CreateError);
    }
    return Ok(shared_from_this());
}

auto OpenGLVertexShader::shaderSource(GLsizei count, const GLchar *const* GLSL_source, const GLint *length)->Result<self,VertexShaderError>{
    OPENGL_EXTENSION_HANDLE->glShaderSource(m_vertexShader, count, GLSL_source, length);
    // TODO: check error
    
    return Ok(shared_from_this());
}
auto OpenGLVertexShader::compileShader()->Result<self,VertexShaderError>{

    return Ok(shared_from_this());
}

}