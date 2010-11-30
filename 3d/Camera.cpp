#include "Camera.h"

using namespace RoadRage;

Camera::Camera(General4x4Matrix proj)
    : m_proj(proj)
{
    this->updateVPCache();
}

Camera::operator General4x4Matrix() const
{
    return m_cachedViewProj;
}

Camera& Camera::pos(Vector v)
{
    m_pos = v;
    this->updateVPCache();

    return *this;
}

Vector Camera::pos() const
{
    return m_pos;
}

Camera& Camera::rot(Quaternion q)
{
    m_rot = q;
    this->updateVPCache();

    return *this;
}

Quaternion Camera::rot() const
{
    return m_rot;
}

Camera& Camera::orbit(Quaternion q)
{
    m_orbit = q;
    this->updateVPCache();

    return *this;
}

Quaternion Camera::orbit() const
{
    return m_orbit;
}

void RoadRage::Camera::updateVPCache()
{
    // Caution here! The camera does the OPPOSITE of all to the scene.
    // we don't "place the camera" but we rather "place the scene".

    // Thus, the camera is NOT placed at 1,0,0 - rather the scene is moved
    // by -1,0,0. This has the same effect, but opengl has no "camera".

    AffineMatrix view = AffineMatrix::rotationQuat(m_rot) * AffineMatrix::translation(-m_pos) * AffineMatrix::rotationQuat(m_orbit);
    m_cachedViewProj = m_proj * view;
}
