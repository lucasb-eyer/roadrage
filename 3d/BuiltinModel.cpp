#include "BuiltinModel.h"

#include "Math/Vector.h"
#include "OpenGLWrapper.h"

using namespace RoadRage;

BuiltinModel::BuiltinModel()
{

}

BuiltinModel::~BuiltinModel()
{

}

BoxModel::BoxModel(ShaderManager* pMgr)
    : m_vao(new VertexArrayObject())
    , m_pShader(pMgr->getOrLoadShader("StaticUni"))
{
    m_vbo.reset(new VertexBufferObject({ 1.0f, 1.0f,-1.0f,
                                         1.0f,-1.0f,-1.0f,
                                        -1.0f,-1.0f,-1.0f,
                                        -1.0f, 1.0f,-1.0f,
                                         1.0f, 1.0f, 1.0f,
                                        -1.0f, 1.0f, 1.0f,
                                        -1.0f,-1.0f, 1.0f,
                                         1.0f,-1.0f, 1.0f}, 3));
    m_ebo.reset(new ElementsBufferObject({0, 3, 2,
                                          2, 1, 0,
                                          4, 0, 1,
                                          1, 7, 4,
                                          6, 5, 4,
                                          4, 7, 6,
                                          2, 3, 5,
                                          5, 6, 2,
                                          3, 0, 4,
                                          4, 5, 3,
                                          6, 7, 1,
                                          1, 2, 6}, 3));

    m_vao->bind();
    m_pShader->setVertexAttribute("aVertexPosition", *m_vbo);
    m_ebo->bind();
    m_vao->unbind();
}

BoxModel::~BoxModel()
{

}

void BoxModel::render(const General4x4Matrix& in_vp)
{
    m_pShader->bind();
    m_vao->bind();

    m_pShader->setUniform("uMaterialDiffuse", Vector(1.0f, 0.0f, 0.0f));
    m_pShader->setUniform("uModelViewProjectionMatrix", in_vp);

    glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_INT, 0);

    Shader::unbind();
    VertexArrayObject::unbind();
}
