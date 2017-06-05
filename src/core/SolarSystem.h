#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include <SolarGlobal.h>

#include <Planet.h>
#include <SolarIniReader.h>
#include <SolarLogger.h>
#include <SolarSettings.h>

#include <QList>


class SolarSystem
{
public:
    SolarSystem(SolarSettings *settings = 0);
    ~SolarSystem();

    void init();

    void draw(bool planet, bool orbit);
    void renderPlanets();
    void renderOrbits();

    // FIXME: @param deltaTime ???
    void calculatePositions(double deltaTime);
    void update(double deltaTime);

    void loadPlanets();

    Planet *getPlanet(int planetId);
    QString getPlanetInfo(int planetId);
    Planet *searchByName(const QString &englishName);

private:
    QList<Planet *> m_planets;

    SolarIniReader m_iniReader = SolarIniReader(SOLAR_SYSTEM_INI_FILE_PATH);

    SolarSettings *__settings;
    SolarLogger    __log = SolarLogger("SolarSystem");
};

#endif  // SOLARSYSTEM_H
