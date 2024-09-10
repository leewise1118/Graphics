#ifndef _FRAGMENTSHADER_H_
#define _FRAGMENTSHADER_H_

#include "ExtensionHandler.h"
#include "Result.h"
#include "BaseType.h"
#include <GL/gl.h>
#include <memory>
#include <string>

namespace OGL{

class FragmentShader{
public:
    FragmentShader(const GLchar* fragmentPath);
    ~FragmentShader();

    
    GLuint glCreateShader(GLenum type);
    auto create()-> FragmentShader&;
    void glShaderSource(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
    auto readGLSLandCompile(const GLchar* fragmentPath)->void;

    auto deleteShader()->bool;

    auto getShader()->GLuint{
        return m_fragmentShader;
    }
private:
    GLuint m_fragmentShader;
};

}
#endif