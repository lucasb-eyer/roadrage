#include "VertexArrayObject.h"

using namespace RoadRage;

VertexBufferObject::VertexBufferObject(const std::vector<float>& in_buf, GLint in_nComponents, GLenum in_usage)
    : id(0)
    , nComponents(in_nComponents)
    , type(GL_FLOAT)
    , normalize(GL_FALSE) // Only useful for integer-like types.
    , stride(nComponents*sizeof(float))
{
    glGenBuffers(1, &this->id);
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
    glBufferData(GL_ARRAY_BUFFER, in_buf.size()*sizeof(float), &in_buf[0], in_usage);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
}

void VertexBufferObject::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBufferObject::~VertexBufferObject()
{
    glDeleteBuffers(1, &this->id);
}

ElementsBufferObject::ElementsBufferObject(const std::vector<int>& in_buf, GLint in_nComponents, GLenum in_usage, GLboolean in_normalize)
    : id(0)
    , nComponents(in_nComponents)
    , type(GL_INT)
    , normalize(in_normalize)
    , stride(nComponents*sizeof(int))
{
    glGenBuffers(1, &this->id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, in_buf.size()*sizeof(int), &in_buf[0], in_usage);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ElementsBufferObject::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
}

void ElementsBufferObject::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

ElementsBufferObject::~ElementsBufferObject()
{
    glDeleteBuffers(1, &this->id);
}

VertexArrayObject::VertexArrayObject()
{
    glGenVertexArrays(1, &this->id);
}

VertexArrayObject::~VertexArrayObject()
{
    glDeleteVertexArrays(1, &this->id);
}

bool VertexArrayObject::bind()
{
    glBindVertexArray(this->id);
    return true;
}

void VertexArrayObject::unbind()
{
    glBindVertexArray(0);
}
