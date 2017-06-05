#ifndef SOLARTEXTURE_H
#define SOLARTEXTURE_H

#include <GL/glu.h>
#include <SolarGlobal.h>

#include <SolarLogger.h>

#include <QString>
#include <QImage>
#include <QFileInfo>
#include <QGLWidget>


class SolarTexture
{
public:
    SolarTexture(const QString &textureMapName);

    uint getTexture();

private:
    bool fileExists(const QString &filePath);

    QString m_textureMapName;
    uint    m_texture;
    bool    m_exist;

    SolarLogger __log = SolarLogger("SolarTexture");
};

#endif  // SOLARTEXTURE_H
