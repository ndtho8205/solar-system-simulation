#include "SolarProjector.h"

SolarProjector::SolarProjector(Vec3d position, Vec3d up, double yaw, double pitch)
    : m_movementSpeed(SOLAR_PROJECTOR_SPEED),
      m_mouseSensitivity(SOLAR_PROJECTOR_MOUSE_SENSITIVTY),
      m_yaw(yaw),
      m_pitch(pitch)
{
    m_position    = position;
    m_upVector    = up;
    m_frontVector = up - position;
    m_rightVector = (m_frontVector ^ m_upVector).normalize();

    m_yaw   = yaw;
    m_pitch = pitch;
}

//
// ---------------------------------------------------------------------------
//

void SolarProjector::lookAt()
{
    Vec3d forward = m_position + m_frontVector;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(m_position.x,
              m_position.y,
              m_position.z,
              forward.x,
              forward.y,
              forward.z,
              m_upVector.x,
              m_upVector.y,
              m_upVector.z);
}

void SolarProjector::perspective(double width, double height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(m_fov, width / height, m_zNear, m_zFar);
    glMatrixMode(GL_MODELVIEW);
}

//
// ---------------------------------------------------------------------------
//

void SolarProjector::processKeyboard(CameraMovement direction, double deltaTime)
{
    GLfloat velocity = m_movementSpeed * deltaTime;

    switch (direction) {
        case FORWARD:
            m_position += m_frontVector * velocity;
            break;
        case BACKWARD:
            m_position -= m_frontVector * velocity;
            break;
        case LEFT:
            m_position -= m_rightVector * velocity;
            break;
        case RIGHT:
            m_position += m_rightVector * velocity;
            break;
        case UP:
            m_position += m_upVector * velocity;
            break;
        case DOWN:
            m_position -= m_upVector * velocity;
            break;
    }
}

void SolarProjector::processMouseMovement(Vec2d offset)
{
    offset *= m_mouseSensitivity;

    m_yaw += offset.x;
    m_pitch += offset.y;

    if (m_pitch > 70.0f)
        m_pitch = 70.0f;
    if (m_pitch < -70.0f)
        m_pitch = -70.0f;
    updateCameraVectors();
}

void SolarProjector::processMouseWheel(double delta)
{
    // forward/backward
    GLfloat velocity = m_movementSpeed * delta / 10;
    m_position += m_frontVector * velocity;

    // zoom
    //    if (m_fov >= 1.0f && m_fov <= PROJECTOR_FOV) {
    //        m_fov -= delta;
    //    }
    //    if (m_fov <= 1.0f)
    //        m_fov = 1.0f;
    //    if (m_fov >= PROJECTOR_FOV)
    //        m_fov = PROJECTOR_FOV;
}

//
// ---------------------------------------------------------------------------
//

void SolarProjector::updateCameraVectors()
{
    m_frontVector.x = cos(DEG2RAD * m_yaw) * cos(DEG2RAD * m_pitch);
    m_frontVector.y = sin(DEG2RAD * m_pitch);
    m_frontVector.z = sin(DEG2RAD * m_yaw) * cos(DEG2RAD * m_pitch);
    m_frontVector.normalize();

    //    m_rightVector.x = -cos(DEG2RAD * m_yaw);
    //    m_rightVector.y = 0;
    //    m_rightVector.z = -sin(DEG2RAD * m_yaw);
    //    m_rightVector.normalize();

    m_rightVector = (m_frontVector ^ Vec3d(0, 0, 1)).normalize();
    m_upVector    = (m_rightVector ^ m_frontVector).normalize();
}
