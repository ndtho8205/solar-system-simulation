#include "SolarMainWidget.h"

#include <SolarGlobal.h>

#include <SolarInfoLabel.h>
#include <SolarPushButton.h>
#include <SolarSettingsDialog.h>

#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>


//
// ---------------------------------------------------------------------------
//

QFrame *         quitFrame;
SolarPushButton *m_quitButton;

QFrame *         animateFrame;
SolarPushButton *m_playButton;
SolarPushButton *m_incTimeSpeedButton;
SolarPushButton *m_decTimeSpeedButton;

QFrame *         settingsFrame;
SolarPushButton *m_planetButton;
SolarPushButton *m_orbitButton;
SolarPushButton *m_texturesButton;
SolarPushButton *m_fullscreenButton;

QFrame *         toolsFrame;
SolarPushButton *m_searchButton;
SolarPushButton *m_screenshotButton;

QFrame *             settingsButtonFrame;
QFrame *             settingsDialogFrame;
SolarPushButton *    m_settingsButton;
SolarSettingsDialog *m_settingsDialog;

SolarInfoLabel *infoLabel;

//
// ---------------------------------------------------------------------------
//

SolarSettings *__settings;

//
// ---------------------------------------------------------------------------
//

void setupUi(SolarMainWidget *parent);
void connectSignals(SolarMainWidget *parent);
QFrame *newFrame(SolarMainWidget *parent, QList<SolarPushButton *> buttonList);

//
// ---------------------------------------------------------------------------
//

#include <QDateTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    __settings = new SolarSettings;
    SolarMainWidget w(0, __settings);


    setupUi(&w);
    connectSignals(&w);


#ifndef SOLAR_DEBUG
    w.showFullScreen();
#else
    w.show();
#endif

    return a.exec();
}


//
// ---------------------------------------------------------------------------
//

void setupUi(SolarMainWidget *parent)
{
    // -----------------------------------------------------------------------

    m_quitButton = new SolarPushButton(parent, ":/icons/quit_white.png");

    QList<SolarPushButton *> quitFrameButtonList;
    quitFrameButtonList.push_back(m_quitButton);

    quitFrame = newFrame(parent, quitFrameButtonList);

    // -----------------------------------------------------------------------

    m_decTimeSpeedButton = new SolarPushButton(parent, ":/icons/decTimeSpeed_white.png");
    m_playButton =
        new SolarPushButton(parent, ":/icons/pause_white.png", ":/icons/play_white.png", true);
    m_incTimeSpeedButton = new SolarPushButton(parent, ":/icons/incTimeSpeed_white.png");

    QList<SolarPushButton *> animateFrameButtonList;
    animateFrameButtonList.push_back(m_decTimeSpeedButton);
    animateFrameButtonList.push_back(m_playButton);
    animateFrameButtonList.push_back(m_incTimeSpeedButton);

    animateFrame = newFrame(parent, animateFrameButtonList);


    // -----------------------------------------------------------------------

    m_fullscreenButton = new SolarPushButton(parent, ":/icons/fullscreen_white.png");
    m_texturesButton   = new SolarPushButton(parent, ":/icons/textures_white.png");
    m_planetButton     = new SolarPushButton(parent, ":/icons/planet_white.png");
    m_orbitButton      = new SolarPushButton(parent, ":/icons/orbit_white.png");

    QList<SolarPushButton *> settingsFrameButtonList;
    settingsFrameButtonList.push_back(m_planetButton);
    settingsFrameButtonList.push_back(m_orbitButton);
    settingsFrameButtonList.push_back(m_texturesButton);
    settingsFrameButtonList.push_back(m_fullscreenButton);

    settingsFrame = newFrame(parent, settingsFrameButtonList);

    // -----------------------------------------------------------------------

    m_searchButton     = new SolarPushButton(parent, ":/icons/search_white.png");
    m_screenshotButton = new SolarPushButton(parent, ":/icons/screenshot_white.png");
    //    m_Button = new SolarPushButton(this, ":/icons/orbit_white.png");
    //    m_Button = new SolarPushButton(this, ":/icons/planet_white.png");

    QList<SolarPushButton *> toolsFrameButtonList;
    toolsFrameButtonList.push_back(m_searchButton);
    toolsFrameButtonList.push_back(m_screenshotButton);
    //    toolsFrameButtonList.push_back(m_Button);
    //    toolsFrameButtonList.push_back(m_Button);

    toolsFrame = newFrame(parent, toolsFrameButtonList);

    // -----------------------------------------------------------------------

    m_settingsButton = new SolarPushButton(parent, ":/icons/settings_white.png");
    m_settingsDialog = new SolarSettingsDialog(parent);

    QList<SolarPushButton *> settingsButtonFrameList;
    settingsButtonFrameList.push_back(m_settingsButton);
    QList<SolarPushButton *> settingsDialogFrameList;

    settingsButtonFrame = newFrame(parent, settingsButtonFrameList);
    settingsDialogFrame = newFrame(parent, settingsDialogFrameList);

    settingsButtonFrame->setStyleSheet(
        "background-color: rgba(78, 74, 74, 0.73); border-radius: 0;");
    settingsButtonFrame->setFixedSize(settingsButtonFrame->sizeHint());
    settingsDialogFrame->setStyleSheet(
        "background-color: rgba(78, 74, 74, 0.73); border-radius: 0;");
    settingsDialogFrame->setFixedSize(m_settingsDialog->size());
    settingsDialogFrame->layout()->addWidget(m_settingsDialog);

    // -----------------------------------------------------------------------

    QHBoxLayout *bottombarLayout = new QHBoxLayout();
    bottombarLayout->setSpacing(5);
    bottombarLayout->setContentsMargins(0, 0, 0, 0);
    bottombarLayout->addWidget(toolsFrame);
    bottombarLayout->addWidget(settingsFrame);
    bottombarLayout->addWidget(animateFrame);
    bottombarLayout->addWidget(quitFrame);

    // -----------------------------------------------------------------------

    QVBoxLayout *leftLayout = new QVBoxLayout();
    leftLayout->setSpacing(0);
    leftLayout->setContentsMargins(0, 0, 0, 0);
    leftLayout->addStretch();
    leftLayout->addWidget(settingsDialogFrame);
    leftLayout->addWidget(settingsButtonFrame);

    // -----------------------------------------------------------------------

    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->setContentsMargins(0, 0, 0, 0);
    rightLayout->addStretch(2);
    rightLayout->addLayout(bottombarLayout);

    // -----------------------------------------------------------------------

    QHBoxLayout *mainLayout = new QHBoxLayout(parent);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addLayout(leftLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(rightLayout);

    // -----------------------------------------------------------------------

    infoLabel = new SolarInfoLabel(parent);
}

void connectSignals(SolarMainWidget *parent)
{
    // -----------------------------------------------------------------------

    parent->connect(m_quitButton, SIGNAL(triggered()), parent, SLOT(close()));


    // -----------------------------------------------------------------------
    // TODO: timeSpeed
    //    connect(m_decTimeSpeedButton, SIGNAL(triggered()), this, SLOT());
    //    connect(m_playButton, SIGNAL(triggered()), this, SLOT());
    //    connect(m_incTimeSpeedButton, SIGNAL(triggered()), this, SLOT());

    // -----------------------------------------------------------------------

    m_fullscreenButton->setChecked(__settings->getFlagFullscreen());
    m_texturesButton->setChecked(__settings->getFlagTextures());
    m_planetButton->setChecked(__settings->getFlagPlanetRender());
    m_orbitButton->setChecked(__settings->getFlagOrbitRender());

    parent->connect(
        m_texturesButton, SIGNAL(toggled(bool)), __settings, SLOT(setFlagTextures(bool)));
    parent->connect(
        m_fullscreenButton, SIGNAL(toggled(bool)), __settings, SLOT(setFlagFullscreen(bool)));
    parent->connect(
        __settings, SIGNAL(flagFullscreenChanged(bool)), parent, SLOT(setWindowFullscreenState()));
    parent->connect(
        m_planetButton, SIGNAL(toggled(bool)), __settings, SLOT(setFlagPlanetRender(bool)));
    parent->connect(
        m_orbitButton, SIGNAL(toggled(bool)), __settings, SLOT(setFlagOrbitRender(bool)));

    // -----------------------------------------------------------------------

    parent->connect(m_screenshotButton, SIGNAL(triggered()), parent, SLOT(takeScreenshot()));
    parent->connect(
        parent, SIGNAL(screenshotTaked(bool)), m_screenshotButton, SLOT(setChecked(bool)));

    // -----------------------------------------------------------------------

    settingsDialogFrame->setVisible(false);
    m_settingsDialog->setVisible(false);

    parent->connect(
        m_settingsButton, SIGNAL(toggled(bool)), settingsDialogFrame, SLOT(setVisible(bool)));
    parent->connect(
        m_settingsButton, SIGNAL(toggled(bool)), m_settingsDialog, SLOT(showDialog(bool)));
    parent->connect(
        m_settingsDialog, SIGNAL(showed(bool)), m_settingsButton, SLOT(setChecked(bool)));
    parent->connect(m_settingsDialog,
                    SIGNAL(planetSizeScaleChanged(int)),
                    __settings,
                    SLOT(setPlanetSizeScale(int)));
    parent->connect(m_settingsDialog,
                    SIGNAL(orbitSizeScaleChanged(int)),
                    __settings,
                    SLOT(setOrbitSizeScale(int)));

    // -----------------------------------------------------------------------

    parent->connect(parent, SIGNAL(planetSelected(QString)), infoLabel, SLOT(setInfo(QString)));
}

QFrame *newFrame(SolarMainWidget *parent, QList<SolarPushButton *> buttonList)
{
    QFrame *frame = new QFrame(parent);
    frame->setStyleSheet("background-color: rgba(78, 74, 74, 0.73); border-radius: 5px;");
    frame->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *frameLayout;
    frameLayout = new QHBoxLayout(frame);

    frameLayout->setSpacing(1);
    frameLayout->setContentsMargins(0, 0, 0, 0);
    foreach (SolarPushButton *button, buttonList) {
        frameLayout->addWidget(button);
    }

    return frame;
}
