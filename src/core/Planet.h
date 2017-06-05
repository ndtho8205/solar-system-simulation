#ifndef PLANET_H
#define PLANET_H

#include <GL/glu.h>
#include <cmath>
#include <SolarGlobal.h>

#include <Vector2.h>
#include <Vector3.h>
#include <SolarLogger.h>
#include <SolarTexture.h>

#include <QList>
#include <QString>
#include <QTextStream>


// TODO: drawRing(), getRingInfo()
class Ring
{
public:
    Ring(float radiusMin, float radiusMax);

    const float m_radiusMin;
    const float m_radiusMax;
};


struct KeplerianElems
{
    double a, a_dot;  // semi-major axis [AU, AU/Cy]
    double e, e_dot;  // eccentricity [rad, rad/Cy]
    double I, I_dot;  // inclination [deg, deg/Cy]
    double L, L_dot;  // mean longitude [deg, deg/Cy]
    double w, w_dot;  // longitude of perihelion [deg, deg/Cy]
    double W, W_dot;  // longitude of the ascending node [deg, deg/century]
    double b, c, s, f;
};


class Planet
{
public:
    enum ThePlanets
    {
        Sun = 10,
        Mercury,
        Venus,
        Earth,
        Mars,
        Jupiter,
        Saturn,
        Uranus,
        Neptune,
        Moon
    };

    Planet(const QString &englishName,
           double         orbitSizeMin,
           double         orbitSizeMax,
           double         inclination,
           double         radius,
           double         revolutionPeriod,
           double         rotationPeriod,
           double         numsatellite,
           double         inclinationOrbit,
           uint           textures);
    ~Planet();

    void render(SolarSettings *__settings);
    void renderOrbit(SolarSettings *__settings);
    void drawRing(SolarSettings *__settings);

    void computePosition(double time);

    // TODO: Picking objects with mouse ray
    //    ThePlanets isCollision(Vec3d rayStart, Vec3d rayEnd);

    void addSatellite(const QString &englishName,
                      double         orbitSizeMin,
                      double         orbitSizeMax,
                      double         inclination,
                      double         radius,
                      double         revolutionPeriod,
                      double         rotationPeriod,
                      double         numsatellite,
                      double         inclinationOrbit,
                      uint           textures);

    void setKeplerianElements(double a,
                              double e,
                              double I,
                              double L,
                              double w,
                              double W,
                              double a_dot,
                              double e_dot,
                              double I_dot,
                              double L_dot,
                              double w_dot,
                              double W_dot,
                              double b,
                              double c,
                              double s,
                              double f);

    int     getPlanetId() const;
    QString getEnglishName() const;
    QString getInfoString() const;
    Vec3d   getPosition() const;

    double getRadius(void) const;

private:
    void addLight(Vec3d pos);

    // TODO: computePosition()
    Vec3d solveKeplerProblem(double time);
    double solveKeplerEquation(double M, double e);

    QString m_englishName;


    // NOTE: Characteristics of Planets
    //          http://www.astronoo.com/en/articles/characteristics-of-planets.html    (1)
    //          https://solarsystem.nasa.gov/planets/earth/facts                       (2)
    double m_orbitSizeMin;
    double m_orbitSizeMax;
    double m_inclination;
    double m_radius;

    double m_revolutionPeriod;
    double m_rotationPeriod;

    double m_numsatellite;
    double m_inclinationOrbit;

    double m_rotation;
    Vec3d  m_position;

    KeplerianElems m_elems;

    uint m_texture;

    Ring *          m_ring;
    QList<Planet *> m_satellites;
    SolarLogger     __log = SolarLogger("Planet");
};

#endif  // PLANET_H
