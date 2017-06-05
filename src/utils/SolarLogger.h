#ifndef SOLARLOGGER_H
#define SOLARLOGGER_H

#include <QDebug>
#include <QList>


class SolarLogger
{
    class Info;

public:
    SolarLogger();

    SolarLogger(const QString &className);

    SolarLogger &addClassName(const QString &className);

    SolarLogger &addFuncName(const QString &funcName);

    SolarLogger &addTitle(const QString &title);

    SolarLogger &addInfo(const QString &title, const QString &description);

    SolarLogger &addInfo(const QString &title, double description);

    SolarLogger &addInfo(const QString &description);

    void disable();

    void enable();

    void d();

    void w();

    void e();

private:
    QString getString();
    void    reset();

    bool        m_state = true;
    QString     m_className;
    QString     m_funcName;
    QString     m_title;
    QList<Info> m_info;
};


class SolarLogger::Info
{
public:
    Info(const QString &title, const QString &description)
    {
        m_title       = title;
        m_description = description;
    }

    operator QString()
    {
        if (m_title.length() == 0)
            return m_description;
        else
            return QString("%1: %2").arg(m_title).arg(m_description);
    }

private:
    QString m_title;
    QString m_description;
};

#endif  // SOLARLOGGER_H
