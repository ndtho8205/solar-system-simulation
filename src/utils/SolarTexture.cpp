#include "SolarTexture.h"


SolarTexture::SolarTexture(const QString &textureMapName)
{
#ifndef SOLAR_DEBUG
    __log.disable();
#endif

    m_textureMapName = QString(":/jpg/%1").arg(textureMapName);

    if (!(m_exist = fileExists(m_textureMapName)))
        __log.addFuncName("SolarTexture()").addTitle(m_textureMapName).e();
}

bool SolarTexture::fileExists(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    return (filePath.length() > 0) && fileInfo.exists() && fileInfo.isFile();
}

uint SolarTexture::getTexture()
{
    QImage text, buff;

    if (!m_exist || !buff.load(m_textureMapName)) {
        __log.addFuncName("getTexture()").addTitle(m_textureMapName).e();
        return -1;
    }

    text = QGLWidget::convertToGLFormat(buff);

    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    //    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    //    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    gluBuild2DMipmaps(
        GL_TEXTURE_2D, 3, text.width(), text.height(), GL_RGBA, GL_UNSIGNED_BYTE, text.bits());


    return m_texture;
}
