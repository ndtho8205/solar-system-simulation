#include "Sky.h"

Sky::Sky(uint texture) : m_texture(texture)
{
}

void Sky::draw()
{
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    glPushMatrix();
    {
        glRotatef(-75, -0.5, 0.5, 1);
        glBindTexture(GL_TEXTURE_2D, m_texture);
        GLUquadricObj *quadric = gluNewQuadric();
        gluQuadricTexture(quadric, GLU_TRUE);
        gluQuadricNormals(quadric, GLU_SMOOTH);
        gluSphere(quadric, 1000.0f, 40, 40);
        gluDeleteQuadric(quadric);
    }

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}
