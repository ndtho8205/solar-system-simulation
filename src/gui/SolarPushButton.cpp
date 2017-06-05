#include "SolarPushButton.h"
#include <QDebug>


SolarPushButton::SolarPushButton(QWidget *parent, const QString &iconPath) : QPushButton(parent)
{
    init(iconPath, "", false);
}

SolarPushButton::SolarPushButton(QWidget *      parent,
                                 const QString &iconOnPath,
                                 const QString &iconOffPath,
                                 bool           isTristate)
    : QPushButton(parent)
{
    init(iconOnPath, iconOffPath, isTristate);
}

//
// ---------------------------------------------------------------------------
//

QSize SolarPushButton::sizeHint() const
{
    return FIXED_SIZE;
}

QSize SolarPushButton::minimumSizeHint() const
{
    return FIXED_SIZE;
}

//
// ---------------------------------------------------------------------------
//

void SolarPushButton::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        setChecked(toggleChecked(m_checked));
        emit(toggled(m_checked));
        emit(triggered());
    }

    QPushButton::mousePressEvent(e);
}

void SolarPushButton::enterEvent(QEvent *event)
{
    animate(true);
    QPushButton::enterEvent(event);
}

void SolarPushButton::leaveEvent(QEvent *event)
{
    animate(false);
    QPushButton::leaveEvent(event);
}

//
// ---------------------------------------------------------------------------
//

void SolarPushButton::setChecked(int b)
{
    m_checked = b;
    updateIcon();
}

void SolarPushButton::setChecked(bool b)
{
    setChecked((int)b);
}

//
// ---------------------------------------------------------------------------
//

void SolarPushButton::init(const QString &iconOnPath, const QString &iconOffPath, bool isTristate)
{
    m_iconOnPath  = iconOnPath;
    m_iconOffPath = iconOffPath;
    m_isTristate  = isTristate;

    setFixedSize(FIXED_SIZE);
    setFlat(true);

    setIconSize(FIXED_SIZE);

    m_effect = new QGraphicsOpacityEffect(this);
    setGraphicsEffect(m_effect);

    updateIcon();
}

int SolarPushButton::toggleChecked(int checked)
{
    if (!m_isTristate) {
        if (checked == ButtonStateOff)
            checked = ButtonStateOn;
        else
            checked = ButtonStateOff;
    } else {
        if (++checked > ButtonStateNoChange)
            checked = ButtonStateOff;
    }
    return checked;
}

void SolarPushButton::setOpacity(double opacity)
{
    m_effect->setOpacity(opacity);
}

void SolarPushButton::updateIcon()
{
    if (m_isTristate) {
        switch (m_checked) {
            case ButtonStateOn:
                setIcon(QIcon(m_iconOnPath));
                setOpacity(OPACITY_END_VALUE);
                break;
            case ButtonStateOff:
                setIcon(QIcon(m_iconOffPath));
                setOpacity(OPACITY_END_VALUE);
                break;
            case ButtonStateNoChange:
                setOpacity(OPACITY_START_VALUE);
                setStyleSheet("border: none;");
                break;
        }
    } else {
        setIcon(QIcon(m_iconOnPath));
        if (m_checked == ButtonStateOn) {
            setOpacity(OPACITY_END_VALUE);
        } else {
            setOpacity(OPACITY_START_VALUE);
            setStyleSheet("border: none;");
        }
    }
}

void SolarPushButton::animate(bool enter)
{
    if (m_isTristate) {
        if (enter)
            setStyleSheet("border: 2px solid white;");
        else
            setStyleSheet("border: none;");
        if (m_checked == ButtonStateNoChange) {
            QPropertyAnimation *animation = new QPropertyAnimation(m_effect, "opacity");
            animation->setDuration(OPACITY_EFFECT_DURATION);
            animation->setStartValue(enter ? OPACITY_START_VALUE : OPACITY_END_VALUE);
            animation->setEndValue(enter ? OPACITY_END_VALUE : OPACITY_START_VALUE);
            animation->start(QAbstractAnimation::DeleteWhenStopped);
        }
    } else {
        if (enter)
            setStyleSheet("border: 2px solid white;");
        else
            setStyleSheet("border: none;");

        if (m_checked == ButtonStateOff) {
            QPropertyAnimation *animation = new QPropertyAnimation(m_effect, "opacity");
            animation->setDuration(OPACITY_EFFECT_DURATION);
            animation->setStartValue(enter ? OPACITY_START_VALUE : OPACITY_END_VALUE);
            animation->setEndValue(enter ? OPACITY_END_VALUE : OPACITY_START_VALUE);
            animation->start(QAbstractAnimation::DeleteWhenStopped);
        }
    }
}
