#include "ExtensionHandler.h"
#include <GL/gl.h>
#include <iostream>
#include <libloaderapi.h>

#define __WINDOWS__ 1

#ifdef __WINDOWS__
    #define LoadDynamicLibrary(dynamicLibraryPath) LoadLibrary(dynamicLibraryPath)
    #define FreeDynamicLibrary(handle) FreeLibrary(handle)
    #define GetFunctionAddress(handle,functionName) GetProcAddress((HMODULE)handle,functionName)
#elif __LINUX__
    #define LoadDynamicLibrary(dynamicLibraryPath) dlopen(dynamicLibraryPath,RTLD_LAZY | RTLD_DEEPBIND)
    #define FreeDynamicLibrary(handle) dlclose(handle)
    #define GetFunctionAddress(handle,functionName) dlsym(handle,functionName)
#endif


namespace OGL {

OpenGLExtensionHandler::OpenGLExtensionHandler()
   :m_hOpenGLLib(nullptr),
    m_pGLGenVertexArrays(nullptr),
    m_pGLVertexAttribPointer(nullptr),
    m_pGLEnableVertexAttribArray(nullptr),
    m_pGLBindVertexArray(nullptr),
    m_pGLGenBuffers(nullptr),
    m_pGLBindBuffer(nullptr),
    m_pGLBufferData(nullptr),
    m_pGLCreateShader(nullptr),
    m_pGLShaderSource(nullptr),
    m_pGLGetShaderiv(nullptr),
    m_pGLGetShaderInfoLog(nullptr),
    m_pGLAttachShader(nullptr),
    m_pGLCompileShader(nullptr),
    m_pGLDeleteShader(nullptr),
    m_pGLLinkProgram(nullptr),
    m_pGLGetProgramiv(nullptr),
    m_pGLGetProgramInfoLog(nullptr),
    m_pGlBindFrameBuffer(nullptr)
    {
    m_hOpenGLLib = LoadDynamicLibrary("opengl32.dll");
    if(!m_hOpenGLLib){
        std::cerr << "LoadLibrary failed" << std::endl;
    }
    initialize();
}

OpenGLExtensionHandler::~OpenGLExtensionHandler(){
    if(m_hOpenGLLib){
        FreeDynamicLibrary((HMODULE)m_hOpenGLLib);
    }

}

void OpenGLExtensionHandler::initialize(){
    m_pGLGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)loadFunction("glGenVertexArrays");
    m_pGLVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)loadFunction("glVertexAttribPointer");
    m_pGLEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYARBPROC)loadFunction("glEnableVertexAttribArray");
    m_pGLBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)loadFunction("glBindVertexArray");

    m_pGLGenBuffers = (PFNGLGENBUFFERSPROC)loadFunction("glGenBuffers");
    m_pGLBindBuffer = (PFNGLBINDBUFFERPROC)loadFunction("glBindBuffer");
    m_pGLBufferData = (PFNGLBUFFERDATAPROC)loadFunction("glBufferData");

    m_pGLCreateShader = (PFNGLCREATESHADERPROC)loadFunction("glCreateShader");
    m_pGLShaderSource = (PFNGLSHADERSOURCEPROC)loadFunction("glShaderSource");
    m_pGLGetShaderiv = (PFNGLGETSHADERIVPROC)loadFunction("glGetShaderiv");
    m_pGLGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)loadFunction("glGetShaderInfoLog");
    m_pGLAttachShader = (PFNGLATTACHSHADERPROC)loadFunction("glAttachShader");
    m_pGLCompileShader = (PFNGLCOMPILESHADERPROC)loadFunction("glCompileShader");
    m_pGLDeleteShader = (PFNGLDELETESHADERPROC)loadFunction("glDeleteShader");

    m_pGLLinkProgram = (PFNGLLINKPROGRAMPROC)loadFunction("glLinkProgram");
    m_pGLGetProgramiv = (PFNGLGETPROGRAMIVPROC)loadFunction("glGetProgramiv");
    m_pGLGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)loadFunction("glGetProgramInfoLog");

    m_pGlBindFrameBuffer = (PFNGLBINDFRAMEBUFFERPROC)loadFunction("glBindFrameBuffer");
}

void* OpenGLExtensionHandler::loadFunction(const char* functionName){
    if(!m_hOpenGLLib){
        std::cerr<<"OpenGL library not loaded"<<std::endl;
        return nullptr;
    }
    void *pFunc = (void*)GetFunctionAddress(m_hOpenGLLib,functionName);
    if(!pFunc){
        std::cerr<<"Failed to load function "<< functionName <<std::endl;
    }
    return pFunc;

}


OpenGLExtensionHandler* OpenGLExtensionHandler::getInstance(){
    static OpenGLExtensionHandler instance;
    return &instance;
}

/**
 * @description: 生成一个VAO
 * @param {GLsizei} n: 指定要生成的VAO数量
 * @param {GLuint} *arrays: 指定一个数组，存储生成的VAO
 * @return {*}
 */
void OpenGLExtensionHandler::glGenVertexArrays(GLsizei n, GLuint *arrays)
{
    if(m_pGLGenVertexArrays){
        m_pGLGenVertexArrays(n,arrays);
    }
}

/**
 * @description: 
 * @param {GLuint} index: 指定要配置的顶点数据，例如在顶点着色器中使用`layout(location = 0)`将顶点属性的位置值设置为`0`
 * @param {GLint} size: 顶点属性的大小。如果顶点属性是一个`vec3`,则大小为3
 * @param {GLenum} type: 指定数据类型，`GL_FLOAT`即表示`vec3`]中的值都是浮点数组成
 * @param {GLboolean} normalized: 是否标准化，即是否将数据映射到[0,1]
 * @param {GLsizei} stride: 步长，连续顶点属性组之间的距离，需小心定义顶点属性之间的间隔
 * @param {void} *pointer: 表示位置数据在缓冲中起始位置的**偏移量**。
 * @return {*}
 */
void OpenGLExtensionHandler::glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer){
    if(m_pGLVertexAttribPointer){
        m_pGLVertexAttribPointer(index,size,type,normalized,stride,pointer);
    }

}
/**
 * @description: 
 * @param {GLuint} index
 * @return {*}
 */
void OpenGLExtensionHandler::glEnableVertexAttribArray(GLuint index){
    if(m_pGLEnableVertexAttribArray){
        m_pGLEnableVertexAttribArray(index);
    }
}

void OpenGLExtensionHandler::glBindVertexArray(GLuint array){
    if(m_pGLBindVertexArray){
        m_pGLBindVertexArray(array);
    }

}

void OpenGLExtensionHandler::glGenBuffers(GLsizei n, GLuint *buffers){
    if(m_pGLGenBuffers){
        m_pGLGenBuffers(n,buffers);
    }

}
void OpenGLExtensionHandler::glBindBuffer(GLenum target, GLuint buffer){
    if(m_pGLBindBuffer){
        m_pGLBindBuffer(target,buffer);
    }

}
void OpenGLExtensionHandler::glBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage){
    if(m_pGLBufferData){
        m_pGLBufferData(target,size,data,usage);
    }   

}

GLuint OpenGLExtensionHandler::glCreateShader(GLenum type){
    if(m_pGLCreateShader){
        return m_pGLCreateShader(type);
    }
    return 0;
}

void OpenGLExtensionHandler::glShaderSource(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length){
    if(m_pGLShaderSource){
        m_pGLShaderSource(shader,count,string,length);
    }
}

void OpenGLExtensionHandler::glGetShaderiv(GLuint shader, GLenum pname, GLint *params){
    if(m_pGLGetShaderiv){
        m_pGLGetShaderiv(shader,pname,params);
    }

}
void OpenGLExtensionHandler::glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog){
    if(m_pGLGetShaderInfoLog){
        m_pGLGetShaderInfoLog(shader,bufSize,length,infoLog);
    }   

}
void OpenGLExtensionHandler::glAttachShader(GLuint program, GLuint shader){
    if(m_pGLAttachShader){
        m_pGLAttachShader(program,shader);
    }   

}
void OpenGLExtensionHandler::glCompileShader(GLuint shader){
    if (m_pGLCompileShader) {
        m_pGLCompileShader(shader);
    
    }

}
void OpenGLExtensionHandler::glDeleteShader(GLuint shader){
    if(m_pGLDeleteShader){
        m_pGLDeleteShader(shader);
    }
}

void OpenGLExtensionHandler::glLinkProgram(GLuint program){
    if(m_pGLLinkProgram){
        m_pGLLinkProgram(program);
    }

}
void OpenGLExtensionHandler::glGetProgramiv(GLuint program, GLenum pname, GLint *params){
    if(m_pGLGetProgramiv){
        m_pGLGetProgramiv(program,pname,params);
    }

}
void OpenGLExtensionHandler::glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog){
    if(m_pGLGetProgramInfoLog){
        m_pGLGetProgramInfoLog(program,bufSize,length,infoLog);
    }
}

}

