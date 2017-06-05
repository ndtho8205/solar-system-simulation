#ifndef SOLARGLOBAL_H
#define SOLARGLOBAL_H

#include <SolarSettings.h>

#include <QString>


namespace SolarGlobal {
    const double DEG2RAD = M_PI / 180.0;
    //
    // ---------------------------------------------------------------------------
    //

    const QString SOLAR_SYSTEM_INI_FILE_PATH = ":/ini/solarsystem.ini";

    const QString SSYSTEM_INI_ENGLISH_NAME_KEY      = "englishName";
    const QString SSYSTEM_INI_PARENT_KEY            = "parent";
    const QString SSYSTEM_INI_ORBIT_SIZE_MIN_KEY    = "orbitSizeMin";
    const QString SSYSTEM_INI_ORBIT_SIZE_MAX_KEY    = "orbitSizeMax";
    const QString SSYSTEM_INI_INCLINATION_KEY       = "inclination";
    const QString SSYSTEM_INI_RADIUS_KEY            = "radius";
    const QString SSYSTEM_INI_REVOLUTION_PERIOD_KEY = "revolutionPeriod";
    const QString SSYSTEM_INI_ROTATION_PERIOD_KEY   = "rotationPeriod";
    const QString SSYSTEM_INI_INCLINATION_ORBIT_KEY = "inclinationOrbit";
    const QString SSYSTEM_INI_NUMBER_SATELLITE_KEY  = "numsatellite";
    const QString SSYSTEM_INI_TEXTURE_PATH_KEY      = "texturePath";

    //
    // ---------------------------------------------------------------------------
    //

    const double ORBIT_SIZE_SCALE = 0.000000001f;
    // const double ORBIT_SIZE_SCALE = 0.000001f;
    const double PLANET_SIZE_SCALE = 0.000001f;
    // const double PLANET_SIZE_SCALE = 0.005f;

    //
    // ---------------------------------------------------------------------------
    //

    const double PROJECTOR_FOV = 55.0;

    const double TIME_SPEED_DELTA = 0.01;

    //
    // ---------------------------------------------------------------------------
    //
}

using namespace SolarGlobal;

#define SOLAR_DEBUG

#endif  // SOLARGLOBAL_H
