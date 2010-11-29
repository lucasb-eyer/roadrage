#include "Shader.h"

#include "3d/Math/Vector.h"
#include "3d/Math/Quaternion.h"
#include "3d/Math/Matrix.h"
#include "Utilities/i18n.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <Utilities/String.h>

using namespace RoadRage;

VertexAttribute::VertexAttribute(const std::string& name, GLuint id, GLenum type, GLint size)
    : name(name)
    , id(id)
    , type(type)
    , size(size)
{
}

Uniform::Uniform(const std::string& name, GLuint id, GLenum type, GLint size)
    : name(name)
    , id(id)
    , type(type)
    , size(size)
{
}

void Uniform::set(const RoadRage::Vector& in_v, GLint iArrayElement)
{
    if(iArrayElement >= this->size)
        throw std::runtime_error(_("Trying to access uniform array out of bounds. Uniform name: ") + this->name);

    switch(this->type) {
    case GL_FLOAT_VEC2:
        glUniform2fv(this->arrayIds[iArrayElement], 1, in_v.array3f());
        break;
    case GL_FLOAT_VEC3:
        glUniform3fv(this->arrayIds[iArrayElement], 1, in_v.array3f());
        break;
    case GL_FLOAT_VEC4:
        glUniform4fv(this->arrayIds[iArrayElement], 1, in_v.array4f());
        break;
    default:
        throw std::runtime_error(_("Type incompatibility while setting the uniform ") + this->name);
    };
}

void Uniform::set(const RoadRage::Quaternion& in_v, GLint iArrayElement)
{
    if(iArrayElement >= this->size)
        throw std::runtime_error(_("Trying to access uniform array out of bounds. Uniform name: ") + this->name);

    switch(this->type) {
    case GL_FLOAT_VEC2:
        glUniform2fv(this->arrayIds[iArrayElement], 1, in_v.array4f());
        break;
    case GL_FLOAT_VEC3:
        glUniform3fv(this->arrayIds[iArrayElement], 1, in_v.array4f());
        break;
    case GL_FLOAT_VEC4:
        glUniform4fv(this->arrayIds[iArrayElement], 1, in_v.array4f());
        break;
    default:
        throw std::runtime_error(_("Type incompatibility while setting the uniform ") + this->name);
    };
}

void Uniform::set(const RoadRage::General4x4Matrix& in_v, bool in_bTranspose, GLint iArrayElement)
{
    if(iArrayElement >= this->size)
        throw std::runtime_error(_("Trying to access uniform array out of bounds. Uniform name: ") + this->name);

    switch(this->type) {
    case GL_FLOAT_MAT4:
        glUniformMatrix4fv(this->arrayIds[iArrayElement], 1, in_bTranspose ? GL_TRUE : GL_FALSE, in_v.array16f());
        break;
    default:
        throw std::runtime_error(_("Type incompatibility while setting the uniform ") + this->name);
    };
}

void Uniform::set(const RoadRage::AffineMatrix& in_v, bool in_bTranspose, GLint iArrayElement)
{
    if(iArrayElement >= this->size)
        throw std::runtime_error(_("Trying to access uniform array out of bounds. Uniform name: ") + this->name);

    switch(this->type) {
    case GL_FLOAT_MAT3:
        glUniformMatrix3fv(this->arrayIds[iArrayElement], 1, in_bTranspose ? GL_TRUE : GL_FALSE, in_v.array9f());
        break;
    case GL_FLOAT_MAT4:
        glUniformMatrix4fv(this->arrayIds[iArrayElement], 1, in_bTranspose ? GL_TRUE : GL_FALSE, in_v.array16f());
        break;
    default:
        throw std::runtime_error(_("Type incompatibility while setting the uniform ") + this->name);
    };
}

void Uniform::setInverse(const RoadRage::General4x4Matrix& in_v, bool in_bTranspose, GLint iArrayElement)
{
    if(iArrayElement >= this->size)
        throw std::runtime_error(_("Trying to access uniform array out of bounds. Uniform name: ") + this->name);

    switch(this->type) {
    case GL_FLOAT_MAT4:
        glUniformMatrix4fv(this->arrayIds[iArrayElement], 1, in_bTranspose ? GL_TRUE : GL_FALSE, in_v.array16fInverse());
        break;
    default:
        throw std::runtime_error(_("Type incompatibility while setting the uniform ") + this->name);
    };
}

void Uniform::setInverse(const RoadRage::AffineMatrix& in_v, bool in_bTranspose, GLint iArrayElement)
{
    if(iArrayElement >= this->size)
        throw std::runtime_error(_("Trying to access uniform array out of bounds. Uniform name: ") + this->name);

    switch(this->type) {
    case GL_FLOAT_MAT3:
        glUniformMatrix3fv(this->arrayIds[iArrayElement], 1, in_bTranspose ? GL_TRUE : GL_FALSE, in_v.array9fInverse());
        break;
    case GL_FLOAT_MAT4:
        glUniformMatrix4fv(this->arrayIds[iArrayElement], 1, in_bTranspose ? GL_TRUE : GL_FALSE, in_v.array16fInverse());
        break;
    default:
        throw std::runtime_error(_("Type incompatibility while setting the uniform ") + this->name);
    };
}

void Uniform::setSampler(unsigned int in_texUnit, GLint iArrayElement)
{
    if(iArrayElement >= this->size)
        throw std::runtime_error(_("Trying to access uniform array out of bounds. Uniform name: ") + this->name);

    switch(this->type) {
    case GL_SAMPLER_2D:
        glUniform1i(this->arrayIds[iArrayElement], (GLint)in_texUnit);
        break;
    default:
        throw std::runtime_error(_("Type incompatibility while setting the uniform ") + this->name);
    };
}

void checkShaderLog(GLuint id, std::string in_sName)
{
    GLint loglen = 0;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &loglen);
    std::vector<GLchar> pszLog(loglen);     // Deleted automatically.
    glGetShaderInfoLog(id, loglen, NULL, &pszLog[0]);

    std::string sLog = &pszLog[0];
    if(!sLog.empty())
        std::cerr << _("Shader info-log of ") << in_sName << ":\n" << sLog << std::endl;
}

void checkProgramLog(GLuint id, std::string in_sName)
{
    GLint loglen = 0;
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &loglen);
    std::vector<GLchar> pszLog(loglen);     // Deleted automatically.
    glGetProgramInfoLog(id, loglen, NULL, &pszLog[0]);

    std::string sLog = &pszLog[0];
    if(!sLog.empty())
        std::cerr << _("Shader info-log of ") << in_sName << ":\n" << sLog << std::endl;
}

bool didShaderCompile(GLuint id)
{
    GLint bCompiled = GL_FALSE;
    glGetShaderiv(id, GL_COMPILE_STATUS, &bCompiled);

    return (bCompiled == GL_TRUE) && (id != 0);
}

bool didProgramLink(GLuint id)
{
    GLint bLinked = GL_FALSE;
    glGetProgramiv(id, GL_LINK_STATUS, &bLinked);

    return (bLinked == GL_TRUE) && (id != 0);
}

Shader::Shader(const std::string& in_sName, const std::string& in_sSourceCodeVert, const std::string& in_sSourceCodeFrag)
{
    // This allows us to use RAII and exception-safety.
    struct CompiledShader {
        GLuint id;
        CompiledShader(GLenum type) : id(glCreateShader(type)) {}
        ~CompiledShader() {glDeleteShader(id);}

        operator GLuint() const {return id;}
    };

    CompiledShader vert(GL_VERTEX_SHADER);
    CompiledShader frag(GL_FRAGMENT_SHADER);

    const char *srcVert = in_sSourceCodeVert.c_str();
    const char *srcFrag = in_sSourceCodeFrag.c_str();
    glShaderSource(vert, 1, &srcVert, 0);
    glShaderSource(frag, 1, &srcFrag, 0);
    glCompileShader(vert);
    glCompileShader(frag);

    // We always get the info log, it might contain some useful warnings!
    checkShaderLog(vert, in_sName + ".vert");
    checkShaderLog(frag, in_sName + ".frag");

    // If there was an error, we throw it as an exception.
    if(!didShaderCompile(vert)) { throw std::runtime_error(_("Failed to compile the shader ") + in_sName + ".vert"); }
    if(!didShaderCompile(frag)) { throw std::runtime_error(_("Failed to compile the shader ") + in_sName + ".frag"); }

    // Now, link those shaders to a program.
    m_id = glCreateProgram();
    glAttachShader(m_id, vert);
    glAttachShader(m_id, frag);
    glLinkProgram(m_id);

    checkProgramLog(m_id, in_sName);
    if(!didProgramLink(m_id)) { throw std::runtime_error(_("Failed to link the shader ") + in_sName); }

    // Say that the fragment shader "out" variable "Color" is the output to the screen (0).
    glBindFragDataLocation(m_id, 0, "Color");

    // If all that worked, we query all attributes and all uniforms that are
    // available in the program and store their informations.

    // First the attributes:
    GLint nAttribs = 0, nLongestAttrib = 0;
    glGetProgramiv(m_id, GL_ACTIVE_ATTRIBUTES, &nAttribs);
    glGetProgramiv(m_id, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &nLongestAttrib);

    for(GLint i = 0 ; i < nAttribs ; ++i) {
        std::vector<GLchar> name(nLongestAttrib);
        GLint size, id;
        GLenum type;
        glGetActiveAttrib(this->id(), i, nLongestAttrib, NULL, &size, &type, &name[0]);
        std::string sName = &name[0];

        // Wow, it took me hours to find out that the id isn't forcedly i!
        id = glGetAttribLocation(m_id, sName.c_str());

        m_attribs.insert(std::make_pair(sName, VertexAttribute(sName, id, type, size)));
    }

    // Then the uniforms:
    GLint nUniforms = 0, nLongestUniform = 0;
    glGetProgramiv(m_id, GL_ACTIVE_UNIFORMS, &nUniforms);
    glGetProgramiv(m_id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &nLongestUniform);

    for(GLint i = 0 ; i < nUniforms ; ++i) {
        GLsizei iActualLen = 0;
        std::vector<GLchar> name(nLongestUniform);
        GLint size, id;
        GLenum type;
        glGetActiveUniform(this->id(), i, nLongestUniform, &iActualLen, &size, &type, &name[0]);
        std::string sName = &name[0];

        // Same story here as for the attribs... Crazy shit!
        id = glGetUniformLocation(m_id, sName.c_str());

        m_uniforms.insert(std::make_pair(sName, Uniform(sName, id, type, size)));

        // In case it is an array, we get the id of every single array entry...
        // But even if it ain't an array, we put the id of the uniform itself
        // in the array's first slot.
        m_uniforms.at(sName).arrayIds.push_back(id);
        for(GLint i = 1 ; i < size ; ++i) {
            m_uniforms.at(sName).arrayIds.push_back(glGetUniformLocation(m_id, (sName + "[" + to_s(i) + "]").c_str()));
        }
    }
}

Shader::~Shader()
{
    if(m_id != 0) {
        glDeleteProgram(m_id);
    }
}

void Shader::bind()
{
    glUseProgram(m_id);
}

void Shader::unbind()
{
    glUseProgram(0);
}

bool Shader::hasUniform(const std::string& in_sName) const
{
    return m_uniforms.find(in_sName) != m_uniforms.end();
}

Uniform Shader::getUniform(const std::string& in_sName)
{
    auto i = m_uniforms.find(in_sName);
    if(i == m_uniforms.end())
        throw std::runtime_error(_("Trying to access an inexistent uniform"));

    return i->second;
}

bool Shader::hasVertexAttribute(const std::string& in_sName) const
{
    return m_attribs.find(in_sName) != m_attribs.end();
}

/// This method binds a vertex buffer to a certain attribute of the shader.
/// \return true if the bind succeeded, false else.
bool Shader::setVertexAttribute(const std::string& in_sName, const RoadRage::VertexBufferObject& in_buffer)
{
    auto i = m_attribs.find(in_sName);
    if(i == m_attribs.end())
        return false;

    // Do some verifications
    if(in_buffer.type == GL_FLOAT) {
        switch(in_buffer.nComponents) {
        case 1:
            if(i->second.type != GL_FLOAT)
                return false;
            break;
        case 2:
            if(i->second.type != GL_FLOAT_VEC2)
                return false;
            break;
        case 3:
            if(i->second.type != GL_FLOAT_VEC3)
                return false;
            break;
        case 4:
            if(i->second.type != GL_FLOAT_VEC4)
                return false;
            break;
        default:
            return false;
        }
    }

    glEnableVertexAttribArray(i->second.id);
    in_buffer.bind();
    glVertexAttribPointer(i->second.id, in_buffer.nComponents, in_buffer.type, in_buffer.normalize, in_buffer.stride, NULL);

    return true;
}

char Shader::fastNrToChar(uint8_t nr)
{
    if(nr<0 || nr>=10)
        throw std::runtime_error(_("Trying to use more than 10 textures in one vertex!"));

    return '0'+char(nr);
}

void Shader::setUniform(const std::string& in_sName, const RoadRage::Vector& in_v, GLint iArrayElement)
{
    try {
        this->getUniform(in_sName).set(in_v, iArrayElement);
    } catch(const std::exception& e) { std::cerr << e.what() << std::endl; }
}

void Shader::setUniform(const std::string& in_sName, const RoadRage::Quaternion& in_v, GLint iArrayElement)
{
    try {
        this->getUniform(in_sName).set(in_v, iArrayElement);
    } catch(const std::exception& e) { std::cerr << e.what() << std::endl; }
}

void Shader::setUniform(const std::string& in_sName, const RoadRage::General4x4Matrix& in_v, bool in_bTranspose, GLint iArrayElement)
{
    try {
        this->getUniform(in_sName).set(in_v, in_bTranspose, iArrayElement);
    } catch(const std::exception& e) { std::cerr << e.what() << std::endl; }
}

void Shader::setUniform(const std::string& in_sName, const RoadRage::AffineMatrix& in_v, bool in_bTranspose, GLint iArrayElement)
{
    try {
        this->getUniform(in_sName).set(in_v, in_bTranspose, iArrayElement);
    } catch(const std::exception& e) { std::cerr << e.what() << std::endl; }
}

void Shader::setUniformInverse(const std::string& in_sName, const RoadRage::General4x4Matrix& in_v, bool in_bTranspose, GLint iArrayElement)
{
    try {
        this->getUniform(in_sName).setInverse(in_v, in_bTranspose, iArrayElement);
    } catch(const std::exception& e) { std::cerr << e.what() << std::endl; }
}

void Shader::setUniformInverse(const std::string& in_sName, const RoadRage::AffineMatrix& in_v, bool in_bTranspose, GLint iArrayElement)
{
    try {
        this->getUniform(in_sName).setInverse(in_v, in_bTranspose, iArrayElement);
    } catch(const std::exception& e) { std::cerr << e.what() << std::endl; }
}

void Shader::setUniformSampler(const std::string& in_sName, unsigned int in_texUnit, GLint iArrayElement)
{
    try {
        this->getUniform(in_sName).setSampler(in_texUnit, iArrayElement);
    } catch(const std::exception& e) { std::cerr << e.what() << std::endl; }
}

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
}

std::string getFileContent(const std::string& in_sFile)
{
    std::ifstream f(in_sFile.c_str());
    if(!f) return "";

    std::stringstream ss;
    ss << f.rdbuf();

    return ss.str();
}

Shader::Ptr ShaderManager::getOrLoadShader(const std::string& in_sName)
{
    auto i = m_mShaders.find(in_sName);
    if(i != m_mShaders.end())
        return i->second;

    // We need to load the shaders from files.
    std::string full = std::string("Data/Shaders/") + in_sName;
    std::string sVert = getFileContent(full + ".vert");
    std::string sFrag = getFileContent(full + ".frag");

    if(sVert.empty() || sFrag.empty()) {
        throw std::runtime_error(_("The following file does not exist: ") + full + "[.vert|.frag]");
    }

    m_mShaders.insert(std::make_pair(in_sName, Shader::Ptr(new Shader(in_sName, sVert, sFrag))));

    return m_mShaders[in_sName];
}
