#ifndef SOLARSETTINGS_H
#define SOLARSETTINGS_H

#include <SolarLogger.h>

#include <QObject>


class SolarSettings : public QObject
{
    Q_OBJECT

public:
    static bool selectionMode;

    SolarSettings(QObject *parent = 0);

    bool getFlagTextures() const
    {
        return m_flagTextures;
    }

    bool getFlagFullscreen() const
    {
        return m_flagFullscreen;
    }

    bool getFlagPlanetRender() const
    {
        return m_flagPlanetRender;
    }

    bool getFlagOrbitRender() const
    {
        return m_flagOrbitRender;
    }

    double getPlanetSizeScale() const
    {
        return m_planetSizeScale;
    }

    double getOrbitSizeScale()
    {
        return m_orbitSizeScale;
    }

    double getTimeSpeed() const
    {
        return m_timeSpeed;
    }

public slots:
    void setFlagTextures(bool b);
    void setFlagFullscreen(bool b);
    void setFlagPlanetRender(bool b);
    void setFlagOrbitRender(bool b);
    void setPlanetSizeScale(int value);
    void setOrbitSizeScale(int value);
    void increaseTimeSpeed();
    void decreaseTimeSpeed();

signals:
    void flagTexturesChanged(bool);
    void flagFullscreenChanged(bool);
    void flagPlanetRenderChanged(bool);
    void flagOrbitRenderChanged(bool);
    void flagPlanetSizeScaleChanged();
    void flagOribitSizeScaleChanged();

private:
    bool m_flagTextures     = true;
    bool m_flagFullscreen   = true;
    bool m_flagPlanetRender = true;
    bool m_flagOrbitRender  = true;

    double m_planetSizeScale;
    double m_orbitSizeScale;

    double m_timeSpeed;

    SolarLogger __log = SolarLogger("SolarSettings");
};

//
// ---------------------------------------------------------------------------
//



#endif  // SOLARSETTINGS_H
