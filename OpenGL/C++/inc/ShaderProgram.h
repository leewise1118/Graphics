#ifndef _SHADERPROGRAM_H_
#define _SHADERPROGRAM_H_
#include <GL/gl.h>
#include "ExtensionHandler.h"
#include "VertexShader.h"
#include "FragmentShader.h"

namespace OGL{

class ShaderProgram{
public:
    ShaderProgram();
    ~ShaderProgram();

    auto create()->ShaderProgram&;
    auto attachShader(VertexShader& vs)->ShaderProgram&;
    auto attachShader(FragmentShader& fs)->ShaderProgram&;
    auto link()->bool;
    auto use()->void;

private:
    GLuint m_shaderProgram;
};

}
#endif