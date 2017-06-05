#include "SolarSystem.h"

SolarSystem::SolarSystem(SolarSettings *settings)
{
#ifndef SOLAR_DEBUG
    __log.disable();
#endif

    __settings = settings;
}

SolarSystem::~SolarSystem()
{
    foreach (Planet *planet, m_planets) {
        delete planet;
        planet = NULL;
    }
}

//
// ---------------------------------------------------------------------------
//

void SolarSystem::init()
{
    loadPlanets();
}

//
// ---------------------------------------------------------------------------
//

void SolarSystem::draw(bool planet, bool orbit)
{
    if (planet)
        renderPlanets();
    if (orbit)
        renderOrbits();
}

void SolarSystem::renderPlanets()
{
    if (__settings->getFlagTextures()) {
        glEnable(GL_TEXTURE_2D);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    } else {
        glDisable(GL_TEXTURE_2D);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    foreach (Planet *planet, m_planets) {
        planet->render(__settings);
    }

    if (__settings->getFlagTextures()) {
        glDisable(GL_TEXTURE_2D);
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void SolarSystem::renderOrbits()
{
    foreach (Planet *planet, m_planets) {
        planet->renderOrbit(__settings);
    }
}

//
// ---------------------------------------------------------------------------
//

void SolarSystem::calculatePositions(double deltaTime)
{
    foreach (Planet *planet, m_planets) {
        planet->computePosition(deltaTime);
    }
}

void SolarSystem::update(double deltaTime)
{
    // TODO: Update
    Q_UNUSED(deltaTime)
}


//
// ---------------------------------------------------------------------------
//


void SolarSystem::loadPlanets()
{
    QStringList planetsList = m_iniReader.getGroupList();

    foreach (QString planet, planetsList) {
        QString englishName = m_iniReader.getString(planet, SSYSTEM_INI_ENGLISH_NAME_KEY, "");
        QString parent      = m_iniReader.getString(planet, SSYSTEM_INI_PARENT_KEY, "");

        double orbitSizeMin = m_iniReader.getDouble(planet, SSYSTEM_INI_ORBIT_SIZE_MIN_KEY, 0);
        double orbitSizeMax = m_iniReader.getDouble(planet, SSYSTEM_INI_ORBIT_SIZE_MAX_KEY, 0);
        double inclination  = m_iniReader.getDouble(planet, SSYSTEM_INI_INCLINATION_KEY, 0);
        double radius       = m_iniReader.getDouble(planet, SSYSTEM_INI_RADIUS_KEY, 0);
        double revolutionPeriod =
            m_iniReader.getDouble(planet, SSYSTEM_INI_REVOLUTION_PERIOD_KEY, 0);
        double rotationPeriod = m_iniReader.getDouble(planet, SSYSTEM_INI_ROTATION_PERIOD_KEY, 0);

        double numsatellite = m_iniReader.getDouble(planet, SSYSTEM_INI_NUMBER_SATELLITE_KEY, 0);
        double inclinationOrbit =
            m_iniReader.getDouble(planet, SSYSTEM_INI_INCLINATION_ORBIT_KEY, 0);

        QString texturePath = m_iniReader.getString(planet, SSYSTEM_INI_TEXTURE_PATH_KEY, "");

        uint textures = SolarTexture(texturePath).getTexture();

        double k = 1.0;

        if (englishName == "Moon")
            k = 5e1;

        if (parent.length() > 0) {
            foreach (Planet *planet, m_planets) {
                if (planet->getEnglishName() == parent) {
                    __log.addFuncName("loadPlanets()").addTitle("parent == getEnglishName()").d();

                    planet->addSatellite(englishName,
                                         orbitSizeMin * k,
                                         orbitSizeMax * k,
                                         inclination,
                                         radius,
                                         revolutionPeriod,
                                         rotationPeriod,
                                         numsatellite,
                                         inclinationOrbit,
                                         textures);
                }
            }
        } else {
            Planet *planet = new Planet(englishName,
                                        orbitSizeMin,
                                        orbitSizeMax,
                                        inclination,
                                        radius,
                                        revolutionPeriod,
                                        rotationPeriod,
                                        numsatellite,
                                        inclinationOrbit,
                                        textures);
            m_planets.push_back(planet);
        }
    }
}

Planet *SolarSystem::getPlanet(int planetId)
{
    foreach (Planet *planet, m_planets) {
        if (planet->getPlanetId() == planetId)
            return planet;
    }
    return NULL;
}

QString SolarSystem::getPlanetInfo(int planetId)
{
    Planet *planet = NULL;
    bool    found  = false;

    if (planetId > 0)
        foreach (planet, m_planets) {
            if (planet->getPlanetId() == planetId) {
                found = true;
                break;
            }
        }
    if (!found)
        return "";
    else
        return planet->getInfoString();
}

Planet *SolarSystem::searchByName(const QString &englishName)
{
    foreach (Planet *planet, m_planets) {
        if (planet->getEnglishName() == englishName)
            return planet;
    }
    return NULL;
}

//
// ---------------------------------------------------------------------------
//
