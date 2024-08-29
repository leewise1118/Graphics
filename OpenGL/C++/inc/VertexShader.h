#ifndef _VERTEXSHADER_H_
#define _VERTEXSHADER_H_

#include "ExtensionHandler.h"
#include "Result.h"
#include "BaseType.h"
#include <GL/gl.h>
#include <memory>

namespace OGL{


class OpenGLVertexShader: public std::enable_shared_from_this<OpenGLVertexShader>{
    using self = std::shared_ptr<OpenGLVertexShader>;
    enum VertexShaderError{
        CreateError,
        DeleteError,

    };

public:
    OpenGLVertexShader();
    ~OpenGLVertexShader();

    auto createShader()->Result<self,VertexShaderError>;
    auto shaderSource()->Result<self,VertexShaderError>;
    auto compileShader()->Result<self,VertexShaderError>;

private:
    GLuint m_vertexShader;
};

}
#endif