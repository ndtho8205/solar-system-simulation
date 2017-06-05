#ifndef SOLARMAINWIDGET_H
#define SOLARMAINWIDGET_H

#include <GL/glu.h>

#include <Axis.h>
#include <Sky.h>
#include <Vector2.h>
#include <Vector3.h>
#include <SolarSystem.h>
#include <SolarLogger.h>
#include <SolarProjector.h>
#include <SolarSettings.h>
#include <SolarSettingsDialog.h>

#include <QOpenGLWidget>
#include <QBasicTimer>
#include <QElapsedTimer>
#include <QLabel>
#include <QFileDialog>


namespace Ui {
    class SolarMainWidget;
}

// TODO: Separate rendering code from window code

class SolarMainWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit SolarMainWidget(QWidget *parent = 0, SolarSettings *settings = 0);
    ~SolarMainWidget();

    // TODO: Picking objects with mouse ray
    //    void createMouseRay(Vec2d pos);
    void handlePlanetSelection(int planetId);
    int selectPlanet(const Vec2d &pos);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void mouseMoveEvent(QMouseEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *e);
    void timerEvent(QTimerEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;

signals:
    void screenshotTaked(bool);
    void planetSelected(const QString &);

public slots:
    void showSettingsDialog();
    void setWindowFullscreenState();
    void takeScreenshot();

private:
    SolarSystem *m_solarSystem;
    Sky *        m_sky;

    bool  m_isSelectMode;
    bool  m_isDragging;
    Vec2d m_mousePressPosition;
    Vec3d m_rayStart;
    Vec3d m_rayEnd;

    QBasicTimer m_timer;
    double      m_time;
    double      m_timeSpeed;
    double      m_speed;

    QElapsedTimer m_timeCounter;
    qint64        m_lastTime;
    double        m_deltaTime;

    QLabel *m_planetInfo;

    SolarProjector *__camera;
    SolarSettings * __settings;
    SolarLogger     __log = SolarLogger("SolarMainWidget");

    Ui::SolarMainWidget *ui;
};

#endif  // SOLARMAINWIDGET_H
