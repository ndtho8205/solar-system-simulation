#include "SolarIniReader.h"

SolarIniReader::SolarIniReader(const QString &iniFilePath)
{
#ifndef SOLAR_DEBUG
    __log.disable();
#endif

    if ((m_exists = fileExists(iniFilePath))) {
        m_iniFilePath = iniFilePath;
        m_settings    = new QSettings(m_iniFilePath, QSettings::IniFormat);
    } else
        __log.addFuncName("SolarIniReader()").addTitle(iniFilePath).e();
}

SolarIniReader::~SolarIniReader()
{
    delete m_settings;
}

//
// ---------------------------------------------------------------------------
//

bool SolarIniReader::fileExists(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    return (filePath.length() > 0) && fileInfo.exists() && fileInfo.isFile();
}

//
// ---------------------------------------------------------------------------
//

QStringList SolarIniReader::getGroupList()
{
    return m_settings->childGroups();
}

//
// ---------------------------------------------------------------------------
//

QVariant SolarIniReader::get(const QString &group, const QString &key, QVariant defaultValue)
{
    QVariant value;
    m_settings->beginGroup(group);
    value = m_settings->value(key, defaultValue);
    m_settings->endGroup();

    return value;
}

bool SolarIniReader::getBoolean(const QString &group, const QString &key, bool defaultValue)
{
    return get(group, key, defaultValue).toBool();
}

double SolarIniReader::getDouble(const QString &group, const QString &key, double defaultValue)
{
    return get(group, key, defaultValue).toDouble();
}

int SolarIniReader::getInt(const QString &group, const QString &key, int defaultValue)
{
    return get(group, key, defaultValue).toInt();
}

QString SolarIniReader::getString(const QString &group,
                                  const QString &key,
                                  const QString &defaultValue)
{
    return get(group, key, defaultValue).toString();
}

//
// ---------------------------------------------------------------------------
//

QVariant SolarIniReader::get(const QString &key, QVariant defaultValue)
{
    return m_settings->value(key, defaultValue);
}

bool SolarIniReader::getBoolean(const QString &key, bool defaultValue)
{
    return get(key, defaultValue).toBool();
}

double SolarIniReader::getDouble(const QString &key, double defaultValue)
{
    return get(key, defaultValue).toDouble();
}

int SolarIniReader::getInt(const QString &key, int defaultValue)
{
    return get(key, defaultValue).toInt();
}

QString SolarIniReader::getString(const QString &key, const QString &defaultValue)
{
    return get(key, defaultValue).toString();
}

//
// ---------------------------------------------------------------------------
//

bool SolarIniReader::has(const QString &group, const QString &key)
{
    bool res = false;
    if (m_settings->childGroups().contains(group, Qt::CaseInsensitive)) {
        m_settings->beginGroup(group);
        res = m_settings->childKeys().contains(key, Qt::CaseInsensitive);
        m_settings->endGroup();
    }
    return res;
}

bool SolarIniReader::has(const QString &key)
{
    return m_settings->childKeys().contains(key, Qt::CaseInsensitive);
}



//
// ---------------------------------------------------------------------------
//
