#include "SolarInfoLabel.h"

SolarInfoLabel::SolarInfoLabel(QWidget *parent) : QLabel(parent)
{
    setGeometry(QRect(10, 15, 300, 200));
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setFocusPolicy(Qt::NoFocus);
}

void SolarInfoLabel::setInfo(const QString &info)
{
    setText(info);
}
