#ifndef _SHADERERROR_H_
#define _SHADERERROR_H_

namespace OGL{
    enum ShaderError{
        Success,
        CreateVertexShaderError,
        CompileVertexShaderError,
        CreateFragmentShaderError,
        CompileFragmentShaderError,
    };

}

#endif