#ifndef SOLARINFOLABEL_H
#define SOLARINFOLABEL_H

#include <QLabel>


class SolarInfoLabel : public QLabel
{
    Q_OBJECT
public:
    explicit SolarInfoLabel(QWidget *parent = 0);

signals:

public slots:
    void setInfo(const QString &info);
};

#endif  // SOLARINFOLABEL_H
