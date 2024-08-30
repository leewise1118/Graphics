#ifndef _VERTEXSHADER_H_
#define _VERTEXSHADER_H_

#include "ExtensionHandler.h"
#include "Result.h"
#include "BaseType.h"
#include <GL/gl.h>
#include <memory>

namespace OGL{


class OpenGLVertexShader: public std::enable_shared_from_this<OpenGLVertexShader>{
    using Ptr = std::shared_ptr<OpenGLVertexShader>;
    enum VertexShaderError{
        CreateError,
        DeleteError,

    };

public:
    OpenGLVertexShader();
    ~OpenGLVertexShader();

    auto createShader()->Result<Ptr,VertexShaderError>;
    auto shaderSource(GLsizei count, const GLchar *const* GLSL_source , const GLint *length)->Result<Ptr,VertexShaderError>;
    auto compileShader()->Result<Ptr,VertexShaderError>;

private:
    GLuint m_vertexShader;
};

}
#endif