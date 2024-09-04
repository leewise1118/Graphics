#ifndef _VERTEXSHADER_H_
#define _VERTEXSHADER_H_

#include "ExtensionHandler.h"
#include "Result.h"
#include "BaseType.h"
#include <GL/gl.h>
#include <memory>
#include "ShaderError.h"

namespace OGL{


class OGLVertexShader: public std::enable_shared_from_this<OGLVertexShader>{
    using Ptr = std::shared_ptr<OGLVertexShader>;
    enum class VertexShaderError{
        Success = 0,
        CreateError,
        CompileError,
    };
public:
    OGLVertexShader();
    ~OGLVertexShader();

    
    GLuint glCreateShader(GLenum type);
    void glShaderSource(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);

    auto Create()-> OGLVertexShader&;
    auto GetSourceFrom(const GLchar *const* GLSL_source)->OGLVertexShader&;
    auto Compile()->OGLVertexShader&;

private:
    GLuint m_vertexShader;
};

}
#endif