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

    void* loadFunction(const char* name);

    void glViewport();

    // VAO
    void glGenVertexArrays(GLsizei n, GLuint *arrays);
    void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
    void glEnableVertexAttribArray(GLuint index);
    void glBindVertexArray(GLuint array);

    // VBO
    void glGenBuffers(GLsizei n, GLuint *buffers);
    void glBindBuffer(GLenum target, GLuint buffer);
    void glBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage);

    // shader
    GLuint glCreateShader(GLenum type);
    void glShaderSource(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
    void glGetShaderiv(GLuint shader, GLenum pname, GLint *params);
    void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
    void glAttachShader(GLuint program, GLuint shader);
    void glCompileShader(GLuint shader);
    void glDeleteShader(GLuint shader);

    // program
    void glLinkProgram(GLuint program);
    void glGetProgramiv(GLuint program, GLenum pname, GLint *params);
    void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);



private:
    void *m_hOpenGLLib;
    // VAO
    PFNGLGENVERTEXARRAYSPROC m_pGLGenVertexArrays;
    PFNGLVERTEXATTRIBPOINTERPROC m_pGLVertexAttribPointer;
    PFNGLENABLEVERTEXATTRIBARRAYARBPROC m_pGLEnableVertexAttribArray;
    PFNGLBINDVERTEXARRAYPROC m_pGLBindVertexArray;

    // VBO
    PFNGLGENBUFFERSPROC m_pGLGenBuffers;
    PFNGLBINDBUFFERPROC m_pGLBindBuffer;
    PFNGLBUFFERDATAPROC m_pGLBufferData;

    // shader
    PFNGLCREATESHADERPROC m_pGLCreateShader;
    PFNGLSHADERSOURCEPROC m_pGLShaderSource;
    PFNGLGETSHADERIVPROC m_pGLGetShaderiv;
    PFNGLGETSHADERINFOLOGPROC m_pGLGetShaderInfoLog;
    PFNGLATTACHSHADERPROC m_pGLAttachShader;
    PFNGLCOMPILESHADERPROC m_pGLCompileShader;
    PFNGLDELETESHADERPROC m_pGLDeleteShader;

    // program
    PFNGLLINKPROGRAMPROC m_pGLLinkProgram;
    PFNGLGETPROGRAMIVPROC m_pGLGetProgramiv;
    PFNGLGETPROGRAMINFOLOGPROC m_pGLGetProgramInfoLog;

    // frame
    PFNGLBINDFRAMEBUFFERPROC m_pGlBindFrameBuffer;


};

}

// TODO: 多线程是不是会出问题？如果多个线程同时访问这个单例，会不会有性能问题？
#define OPENGL_EXTENSION_HANDLE OpenGLExtensionHandler::getInstance()
#endif // _OPENGL_EXTENSION_HANDLER_H__