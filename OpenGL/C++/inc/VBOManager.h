#ifndef _VBOMANAGER_H_
#define _VBOMANAGER_H_

// TODO:
#include <GL/gl.h>
#include "ExtensionHandler.h"
#include "Result.h" 


class OpenGLVBOManager{

public:
    enum VBOError{
        CreateVBOError,
        DeleteVBOError,

        GenBuffersError;
        BindBuffersError;
    };

public:
    OpenGLVBOManager();
    ~OpenGLVBOManager();
    
    auto genBuffers() -> Result<OpenGLVBOManager*,VBOError>;
    auto bindBuffer() -> Result<OpenGLVBOManager*,VBOError>;
    auto bufferData() -> Result<OpenGLVBOManager*,VBOError>;

private:
    GLuint VBO;
};

#endif