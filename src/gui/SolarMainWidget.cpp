#include "SolarMainWidget.h"
#include "ui_SolarMainWidget.h"



SolarMainWidget::SolarMainWidget(QWidget *parent, SolarSettings *settings)
    : QOpenGLWidget(parent), ui(new Ui::SolarMainWidget)
{
#ifndef SOLAR_DEBUG
    __log.disable();
#endif

    QSurfaceFormat fmt;
    fmt = format();
    fmt.setSamples(32);
    setFormat(fmt);

    setWindowFlags(Qt::WindowStaysOnBottomHint);

    __settings = settings;
    __camera   = new SolarProjector;


    ui->setupUi(this);

    // TODO: xem lai thoi gian
    m_time = 0.0f;

    m_speed     = 10;
    m_timeSpeed = 1.5 * 0.03041666666666667f * m_speed;
    m_timer.start(m_speed, this);


    m_lastTime = 0;
}

SolarMainWidget::~SolarMainWidget()
{
    delete ui;
}



//
// ---------------------------------------------------------------------------
//

void SolarMainWidget::initializeGL()
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    //    glDepthFunc(GL_LEQUAL);
    //    glShadeModel(GL_FLAT);
    //    glEnable(GL_CULL_FACE);
    //    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    //    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

    m_sky         = new Sky(SolarTexture("stars.jpg").getTexture());
    m_solarSystem = new SolarSystem(__settings);
    m_solarSystem->init();

    m_timeCounter.start();
}

void SolarMainWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void SolarMainWidget::paintGL()
{
    double currentTime = m_timeCounter.elapsed();
    m_deltaTime        = (currentTime - m_lastTime) / 1e3;
    m_lastTime         = currentTime;


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // -----------------------------------------------------------------------

    __camera->perspective(width(), height());
    __camera->lookAt();

    // -----------------------------------------------------------------------

    //    if (m_isSelectMode) {
    //        createMouseRay(m_mousePressPosition);

    //        ////////////////////////////////////
    //        selectedPlanet = 4;  //_solarSystem
    //        ////////////////////////////////////
    //    }

    // -----------------------------------------------------------------------

    //    Axis::draw();
    m_sky->draw();

    m_solarSystem->calculatePositions(m_time);
    m_solarSystem->draw(__settings->getFlagPlanetRender(), __settings->getFlagOrbitRender());


    m_time += m_timeSpeed;
}


//
// ---------------------------------------------------------------------------
//

void SolarMainWidget::mouseMoveEvent(QMouseEvent *e)
{
    static bool firstMouse = true;

    if ((e->buttons() & Qt::LeftButton) && !m_isDragging)
        m_isDragging = true;

    if (m_isDragging) {
        if (firstMouse) {
            m_mousePressPosition = Vec2d(e->localPos().x(), e->localPos().y());
            firstMouse           = false;
        } else {
            Vec2d currentMousePressPosition = Vec2d(e->localPos().x(), e->localPos().y());
            Vec2d offset(currentMousePressPosition.x - m_mousePressPosition.x,
                         m_mousePressPosition.y - currentMousePressPosition.y);
            //        Vec2d offset               = currentMousePressPosition - m_mousePressPosition;
            m_mousePressPosition = currentMousePressPosition;

            __camera->processMouseMovement(offset);
        }
    }
}

void SolarMainWidget::mousePressEvent(QMouseEvent *e)
{
    m_mousePressPosition = Vec2d(e->localPos().x(), e->localPos().y());

    handlePlanetSelection(selectPlanet(m_mousePressPosition));
}

void SolarMainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    if (!m_isDragging)
        m_isSelectMode = true;
    m_isDragging       = false;
}

void SolarMainWidget::wheelEvent(QWheelEvent *e)
{
    __camera->processMouseWheel(e->delta() / 1000.0);
}

void SolarMainWidget::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
    update();
}

void SolarMainWidget::keyPressEvent(QKeyEvent *e)
{
    __log.addFuncName("keyPressEvent()").addTitle("").addInfo("Key", e->key()).d();
    switch (e->key()) {
        case Qt::Key_Escape:
            QApplication::quit();
            break;
        case Qt::Key_W:
            __camera->processKeyboard(SolarProjector::FORWARD, m_deltaTime);
            break;
        case Qt::Key_S:
            __camera->processKeyboard(SolarProjector::BACKWARD, m_deltaTime);
            break;
        case Qt::Key_A:
            __camera->processKeyboard(SolarProjector::LEFT, m_deltaTime);
            break;
        case Qt::Key_D:
            __camera->processKeyboard(SolarProjector::RIGHT, m_deltaTime);
            break;
        case Qt::Key_I:
            __camera->processKeyboard(SolarProjector::UP, m_deltaTime);
            break;
        case Qt::Key_K:
            __camera->processKeyboard(SolarProjector::DOWN, m_deltaTime);
            break;
    }
}



//
// ---------------------------------------------------------------------------
//

// void SolarMainWidget::createMouseRay(Vec2d pos)
//{
//    double modelView[16], projection[16];
//    int    viewport[4];

//    glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
//    glGetDoublev(GL_PROJECTION_MATRIX, projection);
//    glGetIntegerv(GL_VIEWPORT, viewport);


//    double posX = (double)pos.x;
//    double posY = viewport[3] - pos.y;

//    gluUnProject(posX,
//                 posY,
//                 0.0,
//                 modelView,
//                 projection,
//                 viewport,
//                 &m_rayStart.x,
//                 &m_rayStart.y,
//                 &m_rayStart.z);


//    gluUnProject(
//        posX, posY, 1.0, modelView, projection, viewport, &m_rayEnd.x, &m_rayEnd.y, &m_rayEnd.z);
//}

void SolarMainWidget::showSettingsDialog()
{
    // TODO: SolarSettingsDialog
}

void SolarMainWidget::handlePlanetSelection(int planetId)
{
    //    Planet *planet = m_solarSystem->getPlanet(planetId);

    //    if (planet != NULL) {
    //        m_planetInfo->setText(planet->getInfoString());
    //        m_planetInfo->setVisible(true);
    //    }

    emit planetSelected(m_solarSystem->getPlanetInfo(planetId));
}

int SolarMainWidget::selectPlanet(const Vec2d &pos)
{
    GLuint buff[512];
    GLint  hits;
    GLint  viewport[4];

    glGetIntegerv(GL_VIEWPORT, viewport);
    glSelectBuffer(512, buff);

    glRenderMode(GL_SELECT);
    SolarSettings::selectionMode = true;
    glInitNames();
    glPushName(-1);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    {
        glLoadIdentity();
        gluPickMatrix((GLdouble)pos.x, (GLdouble)(viewport[3] - pos.y), 5.0, 5.0, viewport);
        gluPerspective(__camera->getFov(),
                       (float)width() / (float)height(),
                       __camera->getZNear(),
                       __camera->getZFar());
        glMatrixMode(GL_MODELVIEW);
        __camera->lookAt();
        m_solarSystem->draw(__settings->getFlagPlanetRender(), false);
    }
    glPopMatrix();

    SolarSettings::selectionMode = false;
    hits                         = glRenderMode(GL_RENDER);

    //    glViewport(0, 0, width(), height());
    //    __camera->perspective(width(), height());

    __log.addFuncName("selectPlanet()")
        .addInfo("Hits", QString::number(hits))
        .addInfo("ID", buff[3])
        .d();

    return (hits > 0) ? buff[3] : -100;
}

//
// ---------------------------------------------------------------------------
//

void SolarMainWidget::setWindowFullscreenState()
{
    setWindowState(windowState() ^ Qt::WindowFullScreen);
}

void SolarMainWidget::takeScreenshot()
{
    // FIXME: Crash when app is in fullscreen mode and SaveFileDialog shows.

    QImage image = grabFramebuffer();
    //    QFileDialog fileDialog(this,
    //                           "Save as...",
    //                           "name",
    //                           "PNG (*.png);; BMP (*.bmp);;TIFF (*.tiff *.tif);; JPEG (*.jpg
    //                           *.jpeg)");
    //    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    //    fileDialog.setModal(true);
    //    fileDialog.setWindowModality(Qt::WindowModal);
    //    setWindowFlags(Qt::WindowStaysOnTopHint);
    //    fileDialog.exec();
    //    fileDialog.activateWindow();
    //    fileDialog.raise();

    //    image.save(fileDialog.selectedFiles().first());

    image.save(QFileDialog::getSaveFileName(
        this,
        "Save as...",
        "name",
        "PNG (*.png);; BMP (*.bmp);;TIFF (*.tiff *.tif);; JPEG (*.jpg *.jpeg)"));


    emit screenshotTaked(false);
}

//
// ---------------------------------------------------------------------------
//
