#ifndef _SHADER_H_
#define _SHADER_H_

#include <memory>
#include <GL/gl.h>
#include "Result.h"
#include "ShaderError.h"

namespace OGL{
class OGLShader : public std::enable_shared_from_this<OGLShader>{
    using Ptr = std::shared_ptr<OGLShader>;
    virtual auto Create() ->Result<Ptr,ShaderError> = 0;
    virtual auto Compile()->Result<Ptr,ShaderError> = 0;
    // virtual auto Source(GLsizei count, const GLchar *const* GLSL_source , const GLint *length) ->Result<Ptr,ShaderError> = 0;
    virtual auto Attach() ->Result<Ptr,ShaderError> = 0;
    virtual auto Delete() ->Result<Ptr,ShaderError> = 0;
};

}

#endif