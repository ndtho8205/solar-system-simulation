#include "SolarLogger.h"


SolarLogger::SolarLogger()
{
    reset();
}

SolarLogger::SolarLogger(const QString &className)
{
    reset();
    m_className = className;
}

SolarLogger &SolarLogger::addClassName(const QString &className)
{
    m_className = className;
    return *this;
}

SolarLogger &SolarLogger::addFuncName(const QString &funcName)
{
    m_funcName = funcName;
    return *this;
}

SolarLogger &SolarLogger::addTitle(const QString &title)
{
    m_title = title;
    return *this;
}

SolarLogger &SolarLogger::addInfo(const QString &title, const QString &description)
{
    m_info.push_back(Info(title, description));
    return *this;
}

SolarLogger &SolarLogger::addInfo(const QString &title, double description)
{
    m_info.push_back(Info(title, QString::number(description)));
    return *this;
}

SolarLogger &SolarLogger::addInfo(const QString &description)
{
    m_info.push_back(Info("title", description));
    return *this;
}

void SolarLogger::disable()
{
    m_state = false;
}

void SolarLogger::enable()
{
    m_state = true;
}

//
// ---------------------------------------------------------------------------
//

void SolarLogger::d()
{
    qDebug().noquote() << QString("[DEBUG] %1").arg(getString());
}

void SolarLogger::w()
{
    qWarning().noquote() << QString("[WARN] %1").arg(getString());
}

void SolarLogger::e()
{
    qCritical().noquote() << QString("[ERROR] %1").arg(getString());
}

//
// ---------------------------------------------------------------------------
//

QString SolarLogger::getString()
{
    QString string = QString("[%1] [%2] - %3").arg(m_className).arg(m_funcName).arg(m_title);
    foreach (Info info, m_info) {
        string = string + "\n\t" + QString(info);
    }

    reset();

    return string;
}

void SolarLogger::reset()
{
    m_info.clear();
}
