#include "Planet.h"


Planet::Planet(const QString &englishName,
               double         orbitSizeMin,
               double         orbitSizeMax,
               double         inclination,
               double         radius,
               double         revolutionPeriod,
               double         rotationPeriod,
               double         numsatellite,
               double         inclinationOrbit,
               uint           textures)
    : m_englishName(englishName),
      m_orbitSizeMin(orbitSizeMin),
      m_orbitSizeMax(orbitSizeMax),
      m_inclination(inclination),
      m_radius(radius),
      m_revolutionPeriod(revolutionPeriod),
      m_rotationPeriod(rotationPeriod),
      m_numsatellite(numsatellite),
      m_inclinationOrbit(inclinationOrbit),
      m_texture(textures),
      m_ring(NULL)
{
#ifdef SOLAR_DEBUG
    __log.disable();
#endif
}

Planet::~Planet()
{
    if (m_ring) {
        delete m_ring;
        m_ring = NULL;
    }

    foreach (Planet *satellite, m_satellites) {
        delete satellite;
    }
}

//
// ---------------------------------------------------------------------------
//

void Planet::render(SolarSettings *__settings)
{
    Vec3d  positionScaled = m_position * __settings->getOrbitSizeScale();
    double radiusScaled   = m_radius * __settings->getPlanetSizeScale();
    if (m_englishName == "Sun") {
        qDebug() << radiusScaled << '\t' << m_radius * PLANET_SIZE_SCALE;
        if (fabs(radiusScaled - m_radius * PLANET_SIZE_SCALE) < 1e-7) {
            radiusScaled /= 20;
        } else {
            radiusScaled = radiusScaled / 38;
        }

        addLight(positionScaled);
        glDisable(GL_LIGHTING);
    }

    //    __log.addFuncName("render()")
    //        .addTitle("Position scaled")
    //        .addInfo(QString(positionScaled), "")
    //        .d();
    glPushMatrix();
    {
        glTranslated(positionScaled.x, positionScaled.y, positionScaled.z);

        glPushMatrix();
        {
            glRotated(m_inclination, 1.0f, 0.0f, 0.0f);

            glRotated(m_rotation, 0.0f, 0.0f, 1.0f);

            glLoadName(getPlanetId());
            if (__settings == NULL || __settings->getFlagTextures())
                glBindTexture(GL_TEXTURE_2D, m_texture);
            GLUquadricObj *quadric = gluNewQuadric();
            gluQuadricTexture(quadric, GLU_TRUE);
            gluQuadricNormals(quadric, GLU_SMOOTH);
            gluSphere(quadric, radiusScaled, 40, 40);
            gluDeleteQuadric(quadric);
        }
        drawRing(__settings);

        glPopMatrix();
        foreach (Planet *satellite, m_satellites) {
            satellite->render(__settings);
        }
    }
    glPopMatrix();

    if (m_englishName == "Sun") {
        glEnable(GL_LIGHTING);
    }
}


void Planet::renderOrbit(SolarSettings *__settings)
{
    double orbitSizeScale = __settings->getOrbitSizeScale();
    double alpha          = 0;
    double k = 1, x, y, z = 0;

    glDisable(GL_TEXTURE_2D);
    glColor3f(1.0, 1.0, 0.0);
    glLineWidth(1.0);

    glBegin(GL_LINE_LOOP);
    {
        for (int i = 0; i < 50; i++) {
            k = (cos(alpha) >= 0) ? 1 : -1;

            x = m_orbitSizeMax * k *
                sqrt(1 - pow(sin(alpha), 2));              // x = a * sqrt(1- y^2/b^2)*((+/-)1)
            y = sin(alpha) * m_orbitSizeMin;               // y = b*sin(alpha)
            z = tan(m_inclinationOrbit * M_PI / 180) * y;  //;                             //
                                                           // tan(m_inclination * 360 /
            // m_rotationPeriod) * y;

            glVertex3d(x * orbitSizeScale, y * orbitSizeScale, z * orbitSizeScale);

            alpha = (double)(M_PI / 25) + alpha;
        }
    }
    glEnd();

    Vec3d positionScaled = m_position * orbitSizeScale;

    glPushMatrix();
    {
        glTranslated(positionScaled.x, positionScaled.y, positionScaled.z);
        foreach (Planet *satellite, m_satellites) {
            satellite->renderOrbit(__settings);
        }
    }
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0, 1.0, 1.0);
}

void Planet::drawRing(SolarSettings *__settings)
{
    double planetSizeScale = __settings->getPlanetSizeScale();

    double alpha = 0;  // goc tao he so ao
    double k = 1, x, y, z = 0;
    double m       = 0.0f;
    double delta_m = 0.0f;

    if (m_englishName == "Saturn") {
        m       = 7000.0f;
        delta_m = 80000.0f - 7000.0f;
    } else if (m_englishName == "Uranus") {
        m       = 49751.0f;
        delta_m = 86004.0f - 49751.0f;
    }


    glDisable(GL_TEXTURE_2D);
    for (double j = 0.0; j < m_numsatellite; j++) {
        if (m_englishName == "Saturn") {
            glColor3f(j / m_numsatellite, j / m_numsatellite, 0.0);

        } else if (m_englishName == "Uranus") {
            glColor3f(0.0, j / m_numsatellite, j / m_numsatellite);
        }

        glLineWidth(1.0);

        glBegin(GL_LINE_LOOP);
        {
            for (int i = 0; i < 50; i++) {
                k = (cos(alpha) >= 0) ? 1 : -1;

                x = m * cos(alpha);  // x = a * sqrt(1- y^2/b^2)*((+/-)1)
                y = sin(alpha) * m;  // y = b*sin(alpha)
                z = 0;
                ;  // tan(m_inclination * 360 / m_rotationPeriod) * y;


                glVertex3d(x * planetSizeScale, y * planetSizeScale, z * planetSizeScale);

                alpha = (double)(M_PI / 25) + alpha;
            }
        }
        glEnd();
        m += delta_m / m_numsatellite;
    }
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0, 1.0, 1.0);
}


//
// ---------------------------------------------------------------------------
//

void Planet::computePosition(double time)
{
    double angle = time * M_PI / m_revolutionPeriod;

    double k = (cos(angle) >= 0) ? 1 : -1;
    double y = sin(angle) * m_orbitSizeMin;
    double x = m_orbitSizeMax * sqrt(1 - pow(sin(angle), 2)) * k;
    double z = tan(m_inclinationOrbit * M_PI / 180) * y;  // 0;

    m_position.x = x;
    m_position.y = y;
    m_position.z = z;

    //    m_position.x = sin(angle) * m_orbitSize;
    //    m_position.y = cos(angle) * m_orbitSize;
    //    m_position.z = 0;

    m_rotation = time * 360 / m_rotationPeriod;

    foreach (Planet *satellite, m_satellites)
        satellite->computePosition(time);
}

// Planet::ThePlanets Planet::isCollision(Vec3d rayStart, Vec3d rayEnd)
//{
//    Vec3d  offset    = rayEnd - rayStart;
//    Vec3d  rayVector = offset.normalize();
//    double rayLength = rayStart.distance(rayEnd);

//    Vec3d rayStart2Sphere = sphereCenter - rayStart;
//    float t               = rayStart2Sphere.dot(rayVector);

//    Vec3d closestPoint;

//    if (t <= 0.0f)
//        closestPoint = rayStart;
//    else if (t >= rayLength)
//        closestPoint = rayEnd;
//    else
//        closestPoint = rayStart + rayVector * t;


//    return sphereCenter.distance(closestPoint) <= sphereRadius;
//}

//
// ---------------------------------------------------------------------------
//

void Planet::addSatellite(const QString &englishName,
                          double         orbitSizeMin,
                          double         orbitSizeMax,
                          double         inclination,
                          double         radius,
                          double         revolutionPeriod,
                          double         rotationPeriod,
                          double         numsatellite,
                          double         inclinationOrbit,
                          uint           textures)
{
    Planet *satellite = new Planet(englishName,
                                   orbitSizeMin,
                                   orbitSizeMax,
                                   inclination,
                                   radius,
                                   revolutionPeriod,
                                   rotationPeriod,
                                   numsatellite,
                                   inclinationOrbit,
                                   textures);
    m_satellites.push_back(satellite);
}

//
// ---------------------------------------------------------------------------
//

void Planet::setKeplerianElements(double a,
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
                                  double f)
{
    m_elems.a     = a;
    m_elems.e     = e;
    m_elems.I     = I;
    m_elems.L     = L;
    m_elems.w     = w;
    m_elems.W     = W;
    m_elems.a_dot = a_dot;
    m_elems.e_dot = e_dot;
    m_elems.I_dot = I_dot;
    m_elems.L_dot = L_dot;
    m_elems.w_dot = w_dot;
    m_elems.W_dot = W_dot;
    m_elems.b     = b;
    m_elems.c     = c;
    m_elems.s     = s;
    m_elems.f     = f;
}

//
// ---------------------------------------------------------------------------
//

int Planet::getPlanetId() const
{
    if (m_englishName == "Sun")
        return Planet::Sun;
    if (m_englishName == "Mercury")
        return Planet::Mercury;
    if (m_englishName == "Venus")
        return Planet::Venus;
    if (m_englishName == "Earth")
        return Planet::Earth;
    if (m_englishName == "Mars")
        return Planet::Mars;
    if (m_englishName == "Jupiter")
        return Planet::Jupiter;
    if (m_englishName == "Saturn")
        return Planet::Saturn;
    if (m_englishName == "Uranus")
        return Planet::Uranus;
    if (m_englishName == "Neptune")
        return Planet::Neptune;
    if (m_englishName == "Moon")
        return Planet::Moon;

    return -1;
}

QString Planet::getEnglishName() const
{
    return m_englishName;
}

QString Planet::getInfoString() const
{
    QString     str;
    QTextStream oss(&str);

    oss << QString("<html><head/><body>");
    oss << QString("<p>");
    oss << QString("    <span style=' font-size:26pt; font-weight:600; color:#ffffff;'>%1</span>")
               .arg(m_englishName);
    oss << QString("</p>");
    oss << QString("<p>");
    oss << QString("    <span style=' font-size:12pt; color:#ffffff;'><br/>Radius: </span>");
    oss << QString(
               "    <span style=' font-size:12pt; font-weight:600; color:#ffffff;'>%1 km</span>")
               .arg(QString::number(m_radius));
    oss << QString("</p>");
    oss << QString("<p>");
    oss << QString("    <span style=' font-size:12pt; color:#ffffff;'>Perihelion: %1</span>")
               .arg(QString::number(m_orbitSizeMin));
    //    oss << QString(
    //        "    <span style=' font-size:12pt; color:#ffffff; vertical-align:super;'>6</span>");
    oss << QString("    <span style=' font-size:12pt; color:#ffffff;'> km</span>");
    oss << QString("</p>");
    oss << QString("<p>");
    oss << QString("    <span style=' font-size:12pt; color:#ffffff;'>Aphelion: %1</span>")
               .arg(QString::number(m_orbitSizeMax));
    //    oss << QString(
    //        "    <span style=' font-size:12pt; color:#ffffff; vertical-align:super;'>6</span>");
    oss << QString("    <span style=' font-size:12pt; color:#ffffff;'> km</span>");
    oss << QString("</p>");
    oss << QString("<p>");
    oss << QString(
               "    <span style=' font-size:12pt; color:#ffffff;'>Inclination: %1 degrees </span>")
               .arg(QString::number(m_inclination));
    oss << QString("</p>");
    oss << QString("<p>");
    oss << QString(
               "    <span style=' font-size:12pt; color:#ffffff;'>Orbital Period: %1 days </span>")
               .arg(QString::number(m_revolutionPeriod));
    oss << QString("</p>");
    oss << QString("<p>");
    oss << QString("    <span style=' font-size:12pt; color:#ffffff;'>Rotation Period: %1 hours "
                   "</span>")
               .arg(QString::number(m_rotationPeriod));
    oss << QString("    <span style=' color:#ffffff;'></span>");
    oss << QString("</p>");
    oss << QString("</body></html>");

    oss.flush();
    return str;
}

Vec3d Planet::getPosition() const
{
    return m_position * ORBIT_SIZE_SCALE;
}


double Planet::getRadius() const
{
    return m_radius * PLANET_SIZE_SCALE;
}

//
// ---------------------------------------------------------------------------
//

void Planet::addLight(Vec3d pos)
{
    GLfloat light_ambient[]  = {0.0, 0.0, 0.0, 1.0};
    GLfloat light_diffuse[]  = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = {(float)(pos.x), (float)(pos.y), (float)(pos.z), 1.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHT0);
}



Vec3d Planet::solveKeplerProblem(double time)
{
    double argPerihelion = m_elems.w - m_elems.W;
    double M = m_elems.L - m_elems.w + m_elems.b * time * time + m_elems.c * cos(m_elems.f * time) +
               m_elems.s * sin(m_elems.f * time);

    double e = 1.0000;

    double E = solveKeplerEquation(M, e);

    double P = m_elems.a * (cos(E) - e);
    double Q = m_elems.a * sin(E) * sqrt(1 - e * e);

    double x     = cos(argPerihelion) * P - sin(argPerihelion) * Q;
    double y     = sin(argPerihelion) * P + cos(argPerihelion) * Q;
    double z     = sin(m_elems.I) * x;
    x            = cos(m_elems.I) * x;
    double xtemp = x;
    x            = cos(m_elems.W) * xtemp - sin(m_elems.W) * y;
    y            = sin(m_elems.W) * xtemp + cos(m_elems.W) * y;

    return Vec3d(x, y, z);
}

double Planet::solveKeplerEquation(double M, double e)
{
    double E = M;
    double dE;
    while (true) {
        dE = (E - e * sin(E) - M) / (1 - e * cos(E));
        E -= dE;
        if (abs(dE) < 1e-6)
            break;
    }
    return E;
}


// void Planet::satelliteOrbit()
//{
//    double alpha = 0;  // goc tao he so ao
//    double k = 1, x, y, z = 0;
//    double m = 0.0f;
//    double delta_m = 0.0f;

//    if(m_englishName == "Saturn" ){
//        m = 7000.0f;
//        delta_m = 80000.0f-7000.0f;
//    }
//    else if(m_englishName == "Uranus" ){
//            m = 49751.0f;
//            delta_m = 86004.0f-49751.0f;
//        }


//    glDisable(GL_TEXTURE_2D);
//    for(double j=0.0;j<m_numsatellite;j++){
//       if(m_englishName == "Saturn" ){
//               glColor3f(j/m_numsatellite, j/m_numsatellite, 0.0);

//            }
//            else if(m_englishName == "Uranus" ){
//                    glColor3f(0.0,j/m_numsatellite, j/m_numsatellite);
//                }

//    glLineWidth(1.0);

//    glBegin(GL_LINE_LOOP);
//    {
//        for (int i = 0; i < 50; i++) {
//            k = (cos(alpha) >= 0) ? 1 : -1;

//            x = m * cos(alpha);  // x = a * sqrt(1- y^2/b^2)*((+/-)1)
//            y = sin(alpha) * m;   // y = b*sin(alpha)
//            z = 0;                             // tan(m_inclination * 360 / m_rotationPeriod) * y;

//            glVertex3d(x * PLANET_SIZE_SCALE, y * PLANET_SIZE_SCALE, z * PLANET_SIZE_SCALE);

//            alpha = (double)(M_PI / 25) + alpha;
//        }
//    }
//    glEnd();
//    m += delta_m/m_numsatellite;
//    }
//    glEnable(GL_TEXTURE_2D);
//    glColor3f(1.0, 1.0, 1.0);
//}
