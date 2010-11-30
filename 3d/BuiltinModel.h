#pragma once

#include "VertexArrayObject.h"
#include "Shader.h"

#include <memory>
#include <SFML/Graphics/Shader.hpp>

namespace RoadRage {

class BuiltinModel /*: public Model*/ {
public:
    BuiltinModel();
    virtual ~BuiltinModel();

    virtual void render(const General4x4Matrix& in_vp) = 0;

private:
    // No copying for now!
    BuiltinModel(const BuiltinModel&);
};

class BoxModel : public BuiltinModel {
public:
    BoxModel(ShaderManager& pMgr);
    virtual ~BoxModel();

    virtual void render(const General4x4Matrix& in_vp);

private:
    std::shared_ptr<VertexBufferObject> m_vbo;
    std::shared_ptr<ElementsBufferObject> m_ebo;
    std::shared_ptr<VertexArrayObject> m_vao;

    Shader::Ptr m_pShader;
};

class CsysModel : public BuiltinModel {
public:
    CsysModel(ShaderManager& pMgr);
    virtual ~CsysModel();

    virtual void render(const General4x4Matrix& in_vp);

private:
    std::shared_ptr<VertexBufferObject> m_vbo;
    std::shared_ptr<ElementsBufferObject> m_ebo;
    std::shared_ptr<VertexArrayObject> m_vao;

    Shader::Ptr m_pShader;
};

}
