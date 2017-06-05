#ifndef AXIS_H
#define AXIS_H

#include <GL/glu.h>
#include <Vector3.h>


class Axis
{
public:
    static constexpr double AXIS_LENGTH = 500;

    static void draw()
    {
        Vec3d origin(0, 0, 0);
        Vec3d xAxis(AXIS_LENGTH, 0.0, 0.0);
        Vec3d zAxis(0.0, 0.0, AXIS_LENGTH);
        Vec3d yAxis(0.0, AXIS_LENGTH, 0.0);

        glLineWidth(1.0);

        glBegin(GL_LINES);
        {
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3d(origin.x, origin.y, origin.z);
            glVertex3d(xAxis.x, xAxis.y, xAxis.z);

            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3d(origin.x, origin.y, origin.z);
            glVertex3d(yAxis.x, yAxis.y, yAxis.z);

            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3d(origin.x, origin.y, origin.z);
            glVertex3d(zAxis.x, zAxis.y, zAxis.z);
        }
        glEnd();

        glColor3f(1.0f, 1.0f, 1.0f);
    }

private:
    Axis()
    {
    }
};

#endif  // AXIS_H
