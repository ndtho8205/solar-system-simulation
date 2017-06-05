#ifndef SOLARPROJECTOR_H
#define SOLARPROJECTOR_H

#include <GL/glu.h>
#include <SolarGlobal.h>

#include <Vector2.h>
#include <Vector3.h>


class SolarProjector
{
    static constexpr double SOLAR_PROJECTOR_YAW              = -120.0f;
    static constexpr double SOLAR_PROJECTOR_PITCH            = -30.0f;
    static constexpr double SOLAR_PROJECTOR_SPEED            = 2.0f;
    static constexpr double SOLAR_PROJECTOR_MOUSE_SENSITIVTY = 0.05f;

public:
    enum CameraMovement
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };


    SolarProjector(Vec3d  position = Vec3d(3.0f, 3.0f, 3.0f),
                   Vec3d  up       = Vec3d(0.0f, 0.0f, 1.0f),
                   double yaw      = SOLAR_PROJECTOR_YAW,
                   double pitch    = SOLAR_PROJECTOR_PITCH);


    void lookAt();
    void perspective(double width, double height);

    void processKeyboard(CameraMovement direction, double deltaTime);
    // TODO: mouseMovement()
    void processMouseMovement(Vec2d offset);
    void processMouseWheel(double delta);

    double getFov() const
    {
        return m_fov;
    }

    double getZNear() const
    {
        return m_zNear;
    }

    double getZFar() const
    {
        return m_zFar;
    }

private:
    void updateCameraVectors();


    Vec3d m_position;

    Vec3d m_frontVector;
    Vec3d m_upVector;
    Vec3d m_rightVector;

    double m_movementSpeed;
    double m_mouseSensitivity;
    double m_yaw;
    double m_pitch;

    double m_fov   = PROJECTOR_FOV;
    double m_zNear = 0.001f;
    double m_zFar  = 10000.0f;
};


#endif  // SOLARPROJECTOR_H
