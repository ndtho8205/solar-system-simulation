QT       += core gui opengl
QMAKE_CXXFLAGS += -std=c++11
#CONFIG   += static

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SolarSystemSimulator
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

# ----------------------------------------------------------------------------

INCLUDEPATH += src src/core src/gui src/utils

SOURCES += src/main.cpp \
        src/gui/SolarMainWidget.cpp \
    src/gui/SolarPushButton.cpp \
    src/core/Planet.cpp \
    src/core/SolarSystem.cpp \
    src/core/Sky.cpp \
    src/utils/SolarLogger.cpp \
    src/utils/SolarIniReader.cpp \
    src/utils/SolarTexture.cpp \
    src/utils/SolarProjector.cpp \
    src/utils/SolarSettings.cpp \
    src/gui/SolarInfoLabel.cpp \
    src/gui/SolarSettingsDialog.cpp

HEADERS  += src/gui/SolarMainWidget.h \
    src/gui/SolarPushButton.h \
    src/core/Planet.h \
    src/core/SolarSystem.h \
    src/core/Sky.h \
    src/core/Axis.h \
    src/utils/Vector2.h \
    src/utils/Vector3.h \
    src/utils/Vector4.h \
    src/utils/SolarLogger.h \
    src/utils/SolarIniReader.h \
    src/utils/SolarTexture.h \
    src/utils/SolarProjector.h \
    src/utils/SolarSettings.h \
    src/utils/SolarGlobal.h \
    src/gui/SolarInfoLabel.h \
    src/gui/SolarSettingsDialog.h


FORMS    += src/gui/SolarMainWidget.ui \
    src/gui/SolarSettingsDialog.ui

RESOURCES += \
    data/data.qrc \
    icons/icons.qrc \
    textures/textures.qrc

# ----------------------------------------------------------------------------

win32:LIBS += -lOpengl32 -lGlu32
else:unix:LIBS += -lGL -lGLU

RC_ICONS += solar_system_simulator.ico

