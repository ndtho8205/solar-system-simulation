#ifndef SOLARPUSHBUTTON_H
#define SOLARPUSHBUTTON_H

#include <QPushButton>
#include <QMouseEvent>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>


class SolarPushButton : public QPushButton
{
    Q_OBJECT
public:
    SolarPushButton(QWidget *parent, const QString &iconPath = "");
    SolarPushButton(QWidget *      parent,
                    const QString &iconOnPath,
                    const QString &iconOffPath,
                    bool           isTristate);

    enum
    {
        ButtonStateOff      = 0,
        ButtonStateOn       = 1,
        ButtonStateNoChange = 2,
    };

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

    int isChecked() const;

protected:
    void mousePressEvent(QMouseEvent *e);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

    // signals:
    //    void flagChanged();

signals:
    void toggled(bool);
    void triggered();

public slots:
    void setChecked(int b);
    void setChecked(bool b);

private:
    void init(const QString &iconOnPath, const QString &iconOffPath, bool isTristate);
    int toggleChecked(int checked);
    void setOpacity(double opacity);
    void updateIcon();
    void animate(bool enter);

    QGraphicsOpacityEffect *m_effect;

    int     m_checked = ButtonStateOff;
    bool    m_isTristate;
    QString m_iconOnPath;
    QString m_iconOffPath;

    const QSize FIXED_SIZE              = QSize(36, 36);
    const int   OPACITY_EFFECT_DURATION = 300;
    const float OPACITY_START_VALUE     = 0.1;
    const float OPACITY_END_VALUE       = 1.0;
};

#endif  // SOLARPUSHBUTTON_H
