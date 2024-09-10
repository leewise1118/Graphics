#include "ExtensionHandler.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include <iostream>
#include <libloaderapi.h>
#include <minwindef.h>
#include <qsurfaceformat.h>
#include <qwindow.h>
#include <wingdi.h>
#include <QDebug>

#ifdef __WINDOWS__
    #define LoadDynamicLibrary(dynamicLibraryPath) LoadLibrary(dynamicLibraryPath)
    #define FreeDynamicLibrary(handle) FreeLibrary(handle)
    #define GetFunctionAddress(handle,functionName) GetProcAddress((HMODULE)handle,functionName)
#elif __LINUX__
    #define LoadDynamicLibrary(dynamicLibraryPath) dlopen(dynamicLibraryPath,RTLD_LAZY | RTLD_DEEPBIND)
    #define FreeDynamicLibrary(handle) dlclose(handle)
    #define GetFunctionAddress(handle,functionName) dlsym(handle,functionName)
#endif


#ifdef _DEBUG
#define GL_ERROR_CHECK() do\
{\
    CheckOpenGLError(__FUNCTION__,__FILE__,__LINE__);\
}while(0)
#else
#define GL_ERROR_CHECK()
#endif



namespace OGL {

OpenGLExtensionHandler::OpenGLExtensionHandler()
   :m_hOpenGLLib(nullptr),
    m_context(nullptr),
    m_window(nullptr),
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
    m_pGLCompileShader(nullptr),
    m_pGLDeleteShader(nullptr),

    m_pGLCreateProgram(nullptr),
    m_pGLAttachShader(nullptr),
    m_pGLLinkProgram(nullptr),
    m_pGLUseProgram(nullptr),

    m_pGLGetProgramiv(nullptr),
    m_pGLGetProgramInfoLog(nullptr),
    m_pGlBindFrameBuffer(nullptr),
    m_pGlGetError(nullptr) {
    
    m_window = new QWindow();
    m_window->setSurfaceType(QWindow::OpenGLSurface);

    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CoreProfile);
    m_window->setFormat(format);
    m_window->create();

    m_context = new QOpenGLContext();
    m_context->setFormat(format);
    if (!m_context->create()) {
        qDebug() << "QOpenGLContext::create() failed";
        return;
    }

    if (!m_context->makeCurrent(m_window)) {
        qDebug() << "QOpenGLContext::makeCurrent() failed";
        return;
    }

    m_hOpenGLLib = LoadLibrary("opengl32.dll");
    if (!m_hOpenGLLib) {
        DWORD error = GetLastError();
        std::cerr << "LoadLibrary failed with error code " << error << std::endl;
        return;
    }
    initialize();
}

OpenGLExtensionHandler::~OpenGLExtensionHandler(){
    if(m_hOpenGLLib){
        FreeDynamicLibrary((HMODULE)m_hOpenGLLib);
    }
    //TODO: 为什么这里会报错？
    // if(m_window){
    //     delete m_window;
    // }
    if(m_context){
        delete m_context;
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
    m_pGLCompileShader = (PFNGLCOMPILESHADERPROC)loadFunction("glCompileShader");
    m_pGLDeleteShader = (PFNGLDELETESHADERPROC)loadFunction("glDeleteShader");

    m_pGLCreateProgram = (PFNGLCREATEPROGRAMPROC)loadFunction("glCreateProgram");
    m_pGLAttachShader = (PFNGLATTACHSHADERPROC)loadFunction("glAttachShader");
    m_pGLLinkProgram = (PFNGLLINKPROGRAMPROC)loadFunction("glLinkProgram");
    m_pGLUseProgram = (PFNGLUSEPROGRAMPROC)loadFunction("glUseProgram");
    m_pGLGetProgramiv = (PFNGLGETPROGRAMIVPROC)loadFunction("glGetProgramiv");
    m_pGLGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)loadFunction("glGetProgramInfoLog");

    m_pGlBindFrameBuffer = (PFNGLBINDFRAMEBUFFERPROC)loadFunction("glBindFrameBuffer");

    m_pGlGetError = (PFNGLGETERRORPROC)loadFunction("glGetError");
}

void* OpenGLExtensionHandler::loadFunction(const char* functionName){
    if(!m_hOpenGLLib){
        std::cerr<<"OpenGL library not loaded"<<std::endl;
        return nullptr;
    }
    void* pFunc = nullptr;
    pFunc = (void*)wglGetProcAddress(functionName);
    if(!pFunc || ( pFunc == (void*)0x1) || (pFunc == (void*)0x2) || (pFunc == (void*)0x3) ||(pFunc == (void*)-1) ){
        pFunc = (void*)GetFunctionAddress(m_hOpenGLLib,functionName);
    }
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
/**
 * @description: 将着色器源码附着到着色器对象上
 * @param {GLuint} shader: 着色器对象
 * @param {GLenum} pname: 传递源码字符串数量
 * @param {const GLchar *const*string}: 着色器源码
 * @param {const GLint*} length: TODO:
 * @return {*}
 */
void OpenGLExtensionHandler::glShaderSource(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length){
    if(m_pGLShaderSource){
        m_pGLShaderSource(shader,count,string,length);
    }
}

/**
 * @description: 编译着色器对象
 * @param {GLuint} shader: 着色器对象
 * @return {*}
 */
void OpenGLExtensionHandler::glCompileShader(GLuint shader){
    if (m_pGLCompileShader) {
        m_pGLCompileShader(shader);
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

void OpenGLExtensionHandler::glDeleteShader(GLuint shader){
    if(m_pGLDeleteShader){
        m_pGLDeleteShader(shader);
    }
}

GLuint OpenGLExtensionHandler::glCreateProgram(){
    if(m_pGLCreateProgram){
        return m_pGLCreateProgram();
    }
}
void OpenGLExtensionHandler::glAttachShader(GLuint program, GLuint shader){
    if(m_pGLAttachShader){
        m_pGLAttachShader(program,shader);
    }   
}
void OpenGLExtensionHandler::glLinkProgram(GLuint program){
    if(m_pGLLinkProgram){
        m_pGLLinkProgram(program);
    }

}
void OpenGLExtensionHandler::glUseProgram(GLuint program){
    if(m_pGLUseProgram){
        m_pGLUseProgram(program);
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

GLenum OpenGLExtensionHandler::glGetError(){
    if(m_pGlGetError){
        return m_pGlGetError();
    }else{
        return GL_NO_ERROR;
    }
}

void OpenGLExtensionHandler::CheckOpenGLError(const char* func, const char* fname, int line){
    GLenum errorCode;
    while((errorCode = glGetError()) != GL_NO_ERROR){
        std::string error;
        switch(errorCode){
            case GL_INVALID_ENUM:
                error = "INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                error = "INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                error = "INVALID_OPERATION";
                break;
            case GL_STACK_OVERFLOW:
                error = "STACK_OVERFLOW";
                break;
            case GL_STACK_UNDERFLOW:
                error = "STACK_UNDERFLOW";
                break;
            case GL_OUT_OF_MEMORY:
                error = "OUT_OF_MEMORY";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                error = "INVALID_FRAMEBUFFER_OPERATION";
                break;
        }
        printf("OpenGL error %s, at %s:%i - for %s\t\n",error.c_str(),fname,line,func);
    }
}

}

