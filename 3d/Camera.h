#pragma once

#include "Math/Matrix.h"
#include "Math/Quaternion.h"
#include "Math/Vector.h"

namespace RoadRage {

class Camera {
public:
    Camera(General4x4Matrix proj);

    Camera& pos(Vector v);
    Vector pos() const;

    Camera& rot(Quaternion q);
    Quaternion rot() const;

    Camera& orbit(Quaternion q);
    Quaternion orbit() const;

    Camera& orbitCenter(Vector v);
    Vector orbitCenter() const;

    operator General4x4Matrix() const;

protected:
    void updateVPCache();

private:
    Vector m_pos;
    Quaternion m_rot;
    Quaternion m_orbit;
    Vector m_orbitCenter;

    General4x4Matrix m_proj;
    General4x4Matrix m_cachedViewProj;
};

}
