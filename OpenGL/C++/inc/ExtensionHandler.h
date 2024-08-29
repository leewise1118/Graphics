#ifndef _OPENGL_EXTENSION_HANDLER_H_
#define _OPENGL_EXTENSION_HANDLER_H_

#include "BaseType.h"
#include <GL/gl.h>
#include <GL/glext.h> // 定义了很多OpenGL函数指针

namespace OGL{

class OpenGLExtensionHandler
{
public:
    OpenGLExtensionHandler();
    ~OpenGLExtensionHandler();

    static OpenGLExtensionHandler* getInstance();

    void initialize();

    void loadFunction(const char* name);

    void glViewport();

    // VAO
    void glGenVertexArrays(GLsizei n, GLuint *arrays);
    void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
    void glEnableVertexAttribArray(GLuint index);
    void glBindVertexArray(GLuint array);

    // VBO
    void glGenBuffers();
    void glBindBuffer();
    void glBufferData();

    // shader
    GLuint glCreateShader(GLenum type);
    void glShaderSource(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
    void glGetShaderiv();
    void glGetShaderInfoLog();
    void glAttachShader();
    void glCompileShader();
    void glDeleteShader();

    // program
    void glLinkProgram();
    void glGetProgramiv();
    void glGetProgramInfoLog();



private:
    // VAO
    PFNGLGENVERTEXARRAYSPROC m_pGLGenVertexArrays;
    PFNGLVERTEXATTRIBPOINTERPROC m_pGLVertexAttribPointer;
    PFNGLENABLEVERTEXATTRIBARRAYARBPROC m_pGLEnableVertexAttribArray;
    PFNGLBINDVERTEXARRAYPROC m_pGLBindVertexArray;

    // VBO

    // shader
    PFNGLCREATESHADERPROC m_pGLCreateShader;
    PFNGLSHADERSOURCEPROC m_pGLShaderSource;

    // program

    // frame
    PFNGLBINDFRAMEBUFFERPROC m_pGlBindFrameBuffer;

};

}

#define OPENGL_EXTENSION_HANDLE OpenGLExtensionHandler::getInstance()
#endif // _OPENGL_EXTENSION_HANDLER_H__