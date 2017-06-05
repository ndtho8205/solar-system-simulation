#ifndef SOLARSETTINGSDIALOG_H
#define SOLARSETTINGSDIALOG_H

#include "ui_SolarSettingsDialog.h"

#include <QWidget>


namespace Ui {
    class SolarSettingsDialog;
}


class SolarSettingsDialog : public QWidget, public Ui::SolarSettingsDialog
{
    Q_OBJECT

public:
    explicit SolarSettingsDialog(QWidget *parent = 0);
    ~SolarSettingsDialog();

signals:
    void showed(bool);
    void planetSizeScaleChanged(int value);
    void orbitSizeScaleChanged(int value);

public slots:
    void showDialog(bool);
    void changePlanetSizeScale(int value);
    void changeOrbitSizeScale(int value);

private:
};

#endif  // SOLARSETTINGSDIALOG_H
