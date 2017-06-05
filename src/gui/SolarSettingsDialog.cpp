#include "SolarSettingsDialog.h"


SolarSettingsDialog::SolarSettingsDialog(QWidget *parent) : QWidget(parent)
{
    setFixedSize(400, 86);

    setupUi(this);

    connect(
        m_planetScalingSlider, SIGNAL(valueChanged(int)), this, SLOT(changePlanetSizeScale(int)));
    connect(m_orbitScalingSlider, SIGNAL(valueChanged(int)), this, SLOT(changeOrbitSizeScale(int)));
}

SolarSettingsDialog::~SolarSettingsDialog()
{
    //    delete ui;
}

void SolarSettingsDialog::showDialog(bool b)
{
    setVisible(b);
    emit showed(b);
}

void SolarSettingsDialog::changePlanetSizeScale(int value)
{
    emit planetSizeScaleChanged(value);
}

void SolarSettingsDialog::changeOrbitSizeScale(int value)
{
    emit orbitSizeScaleChanged(value);
}
