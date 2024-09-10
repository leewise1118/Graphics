#ifndef _MACRODEFINE_H_
#define _MACRODEFINE_H_

#include "ExtensionHandler.h"
#ifdef _DEBUG
#define glGenVertexArraysD(n,arrays)\
{\
    OPENGL_EXTENSION_HANDLE->glGenVertexArrays(n,arrays);\
    GL_ERROR_CHECK();\
}

#define glBindVertexArrayD(array)\
{\
    OPENGL_EXTENSION_HANDLE->glBindVertexArray(array);\
    GL_ERROR_CHECK();\
}

#define glDeleteVertexArraysD(n,arrays)\
{\
    OPENGL_EXTENSION_HANDLE->glDeleteVertexArrays(n,arrays);\
    GL_ERROR_CHECK();\
}

// Shader
#define glShaderSourceD(shader,count,source,length)\
{\
    OPENGL_EXTENSION_HANDLE->glShaderSource(shader,count,source,length);\
    GL_ERROR_CHECK();\
}

#define glCompileShaderD(shader)\
{\
    OPENGL_EXTENSION_HANDLE->glCompileShader(shader);\
    GL_ERROR_CHECK();\
}

#define glGetShaderivD(shader,pname,params)\
{\
    OPENGL_EXTENSION_HANDLE->glGetShaderiv(shader,pname,params);\
    GL_ERROR_CHECK();\
}

#define glGetShaderInfoLogD(shader,bufsize,length,infolog)\
{\
    OPENGL_EXTENSION_HANDLE->glGetShaderInfoLog(shader,bufsize,length,infolog);\
    GL_ERROR_CHECK();\
}

// Program
#define glCreateProgramD()\
{\
    OPENGL_EXTENSION_HANDLE->glCreateProgram()\
    GL_ERROR_CHECK();\
}

#define glAttachShaderD(program,shader)\
{\
    OPENGL_EXTENSION_HANDLE->glAttachShader(program,shader);\
    GL_ERROR_CHECK();\
}

#define glLinkProgramD(program)\
{\
    OPENGL_EXTENSION_HANDLE->glLinkProgram(program);\
    GL_ERROR_CHECK();\
}

#define glUseProgramD(program)\
{\
    OPENGL_EXTENSION_HANDLE->glUseProgram(program);\
    GL_ERROR_CHECK();\
}

#define glGetProgramivD(program,pname,params)\
{\
    OPENGL_EXTENSION_HANDLE->glGetProgramiv(program,pname,params);\
    GL_ERROR_CHECK();\
}

#endif


#endif