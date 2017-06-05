#ifndef SOLARINIREADER_H
#define SOLARINIREADER_H

#include <SolarGlobal.h>

#include <SolarLogger.h>

#include <QSettings>
#include <QStringList>
#include <QFileInfo>


class SolarIniReader
{
public:
    SolarIniReader(const QString &iniFilePath);
    ~SolarIniReader();

    QStringList getGroupList();

    bool getBoolean(const QString &group, const QString &key, bool defaultValue);
    double getDouble(const QString &group, const QString &key, double defaultValue);
    int getInt(const QString &group, const QString &key, int defaultValue);
    QString getString(const QString &group, const QString &key, const QString &defaultValue);


    bool getBoolean(const QString &key, bool defaultValue);
    double getDouble(const QString &key, double defaultValue);
    int getInt(const QString &key, int defaultValue);
    QString getString(const QString &key, const QString &defaultValue);

    bool has(const QString &group, const QString &key);
    bool has(const QString &key);

private:
    bool fileExists(const QString &filePath);
    QVariant get(const QString &group, const QString &key, QVariant defaultValue);
    QVariant get(const QString &key, QVariant defaultValue);

    bool       m_exists;
    QSettings *m_settings;
    QString    m_iniFilePath;

    SolarLogger __log = SolarLogger("SolarIniReader");
};

#endif  // SOLARINIREADER_H
