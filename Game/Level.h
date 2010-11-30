#pragma once

#include "Avatar.h"
#include "Civilian.h"
#include "GameClock.h"

#include "3d/Camera.h"
#include "3d/Shader.h"
#include "Conf/Configuration.h"

#include <string>
#include <memory>
#include <list>

namespace RoadRage {

class Level {
public:
    typedef std::shared_ptr<Level> Ptr;

    static Level::Ptr load(const Configuration& in_settings, const std::string& in_sName);

    virtual void think(const GameClock& clock);
    virtual void render(const GameClock& clock);

protected:
    Level(const Configuration& in_settings, const std::string& in_sName);

    ShaderManager m_shaderManager;
    Camera m_cam;
    CsysModel m_csys;

    Avatar* m_pAvatar;
    std::list<Civilian*> m_civs;
};

}
