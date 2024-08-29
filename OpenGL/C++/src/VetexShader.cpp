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

auto OpenGLVertexShader::shaderSource()->Result<self,VertexShaderError>{

}
auto OpenGLVertexShader::compileShader()->Result<self,VertexShaderError>{

}

}