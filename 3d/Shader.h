#pragma once

#include "3d/VertexArrayObject.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace RoadRage {
    class Vector;
    class Quaternion;
    class General4x4Matrix;
    class AffineMatrix;

struct VertexAttribute {
    std::string name;
    GLuint id;
    GLenum type;
    GLint size;

    VertexAttribute(const std::string& name, GLuint id, GLenum type, GLint size);
};

struct Uniform {
    std::string name;
    GLuint id;
    GLenum type;
    GLint size;

    // Contains the ids of array elements.
    std::vector<GLuint> arrayIds;

    Uniform(const std::string& name, GLuint id, GLenum type, GLint size);

    void set(const Vector& in_v, GLint iArrayElement = 0);
    void set(const Quaternion& in_v, GLint iArrayElement = 0);
    void set(const General4x4Matrix& in_v, bool in_bTranspose = false, GLint iArrayElement = 0);
    void set(const AffineMatrix& in_v, bool in_bTranspose = false, GLint iArrayElement = 0);
    void setInverse(const General4x4Matrix& in_v, bool in_bTranspose = false, GLint iArrayElement = 0);
    void setInverse(const AffineMatrix& in_v, bool in_bTranspose = false, GLint iArrayElement = 0);
    void setSampler(unsigned in_texUnit, GLint iArrayElement = 0);
};

/// This class represents a fully-linked shader composed of a vertex shader,
/// a fragment shader and optionally a geometry shader.
class Shader {
public:
    virtual ~Shader();

    bool hasVertexAttribute(const std::string& in_sAttribName) const;
    bool setVertexAttribute(const std::string& in_sAttribName, const VertexBufferObject& in_buffer);

    bool hasUniform(const std::string& in_sName) const;
    Uniform getUniform(const std::string& in_sName);

    void setUniform(const std::string& in_sName, const Vector& in_v, GLint iArrayElement = 0);
    void setUniform(const std::string& in_sName, const Quaternion& in_v, GLint iArrayElement = 0);
    void setUniform(const std::string& in_sName, const General4x4Matrix& in_v, bool in_bTranspose = false, GLint iArrayElement = 0);
    void setUniform(const std::string& in_sName, const AffineMatrix& in_v, bool in_bTranspose = false, GLint iArrayElement = 0);
    void setUniformInverse(const std::string& in_sName, const General4x4Matrix& in_v, bool in_bTranspose = false, GLint iArrayElement = 0);
    void setUniformInverse(const std::string& in_sName, const AffineMatrix& in_v, bool in_bTranspose = false, GLint iArrayElement = 0);
    void setUniformSampler(const std::string& in_sName, unsigned in_texUnit, GLint iArrayElement = 0);

    void bind();
    static void unbind();

    GLuint id() const {return m_id;};

    typedef std::shared_ptr<Shader> Ptr;

private:
    friend class ShaderManager;

    // I belong to the shader manager.
    Shader(const std::string& in_sName, const std::string& in_sSourceCodeVert, const std::string& in_sSourceCodeFrag);

    char fastNrToChar(uint8_t nr);

    GLuint m_id;        ///< Contains the OpenGL ID of the compiled shader.
    std::string m_sLog; ///< Might contain infos/warnings/errors about the shader.

    std::map<std::string, VertexAttribute> m_attribs;
    std::map<std::string, Uniform> m_uniforms;
};

/// This is the shader manager that keeps track of all existing shaders,
/// creates new shaders, combines them and deletes them.\n
class ShaderManager {
public:
    ShaderManager();
    virtual ~ShaderManager();

    Shader::Ptr getOrLoadShader(const std::string& in_sName);

private:
    std::map<std::string, Shader::Ptr> m_mShaders;
};

}
