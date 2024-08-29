#include "ExtensionHandler.h"
#include <GL/gl.h>

namespace OGL {

OpenGLExtensionHandler::OpenGLExtensionHandler(){


}

OpenGLExtensionHandler::~OpenGLExtensionHandler(){

}

void OpenGLExtensionHandler::initialize(){

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

}

void OpenGLExtensionHandler::glBindVertexArray(GLuint array){

}

GLuint OpenGLExtensionHandler::glCreateShader(GLenum type){
    if(m_pGLCreateShader){
        return m_pGLCreateShader(type);
    }
    return 0;
}

}

