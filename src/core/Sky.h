#ifndef SKY_H
#define SKY_H

#include <GL/glu.h>

#include <SolarTexture.h>


class Sky
{
public:
    Sky(uint texture);

    void draw();

private:
    uint m_texture;
};

#endif  // SKY_H
