#ifndef _VERTEXSHADER_H_
#define _VERTEXSHADER_H_

#include "ExtensionHandler.h"
#include "Result.h"
#include "BaseType.h"
#include <GL/gl.h>
#include <memory>
#include <string>

namespace OGL{


class VertexShader{
public:
    VertexShader(const GLchar* vertexPath);
    ~VertexShader();

    
    GLuint glCreateShader(GLenum type);
    void glShaderSource(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);

    auto create()-> VertexShader&;
    auto readGLSLandCompile(const GLchar* vertexPath)->void;
    auto deleteShader()->bool;

    auto getShader()->GLuint{
        return m_vertexShader;
    }

private:
    GLuint m_vertexShader;
};

}
#endif