#include "SolarSettings.h"

#include <SolarGlobal.h>


bool SolarSettings::selectionMode = false;


SolarSettings::SolarSettings(QObject *parent) : QObject(parent)
{
#ifndef SOLAR_DEBUG
    __log.disable();
#endif

    m_planetSizeScale = PLANET_SIZE_SCALE;
    m_orbitSizeScale  = ORBIT_SIZE_SCALE;
}

void SolarSettings::setFlagTextures(bool b)
{
    __log.addFuncName("setFlagTextures").addTitle(QString::number(b)).d();
    m_flagTextures = b;
    emit flagTexturesChanged(b);
}

void SolarSettings::setFlagFullscreen(bool b)
{
    __log.addFuncName("setFlagFullscreen").addTitle(QString::number(b)).d();
    m_flagFullscreen = b;
    emit flagFullscreenChanged(b);
}

void SolarSettings::setFlagPlanetRender(bool b)
{
    __log.addFuncName("setFlagPlanetRender").addTitle(QString::number(b)).d();
    m_flagPlanetRender = b;
    emit flagPlanetRenderChanged(b);
}

void SolarSettings::setFlagOrbitRender(bool b)
{
    __log.addFuncName("setFlagOrbitRender").addTitle(QString::number(b)).d();
    m_flagOrbitRender = b;
    emit flagOrbitRenderChanged(b);
}

void SolarSettings::setPlanetSizeScale(int value)
{
    m_planetSizeScale = PLANET_SIZE_SCALE * value;
    emit flagPlanetSizeScaleChanged();
}

void SolarSettings::setOrbitSizeScale(int value)
{
    m_orbitSizeScale = ORBIT_SIZE_SCALE * value;
    emit flagOribitSizeScaleChanged();
}

void SolarSettings::increaseTimeSpeed()
{
    m_timeSpeed += 0.5;  // TIME_SPEED_DELTA;
}

void SolarSettings::decreaseTimeSpeed()
{
    m_timeSpeed -= 0.5;  // TIME_SPEED_DELTA;
}
