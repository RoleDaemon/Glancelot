#include "glancelot/theme_manager.hpp"
#include <QGuiApplication>
#include <QStyleHints>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSaveFile>

namespace {
QString settingsPath() {
    QString directory=qEnvironmentVariable("GLANCELOT_CONFIG_DIR");
    if(directory.isEmpty())directory=QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    return QDir(directory).filePath("settings.json");
}
}
ThemeManager::ThemeManager(QObject* parent):QObject(parent) {
    QFile catalog(":/themes/catalog.json");
    if(catalog.open(QIODevice::ReadOnly)) m_families=QJsonDocument::fromJson(catalog.readAll()).array().toVariantList();
    QFile settings(settingsPath());
    if(settings.open(QIODevice::ReadOnly)&&settings.size()<=1024*1024) {
        const auto root=QJsonDocument::fromJson(settings.readAll()).object();
        if(root.value("schema").toInt()==1) {
            const auto appearance=root.value("appearance").toObject();
            const auto selected=appearance.value("family").toString();
            if(!preview(selected,true).isEmpty())m_family=selected;
            const auto mode=appearance.value("mode").toString();
            if(mode=="system"||mode=="dark"||mode=="light")m_mode=mode;
        }
    }
    if(qGuiApp)connect(qGuiApp->styleHints(),&QStyleHints::colorSchemeChanged,this,[this]{if(m_mode=="system")emit changed();});
}
bool ThemeManager::dark() const {
    return m_mode=="dark" || (m_mode=="system" && (!qGuiApp || qGuiApp->styleHints()->colorScheme()!=Qt::ColorScheme::Light));
}
QVariantMap ThemeManager::preview(const QString& family,bool isDark) const {
    for(const auto& row:m_families) {const auto value=row.toMap();if(value.value("id").toString()==family)return value.value(isDark?"dark":"light").toMap();}
    return {};
}
QVariantMap ThemeManager::colors() const {return preview(m_family,dark());}
void ThemeManager::setFamily(const QString& family) {if(family==m_family||preview(family,true).isEmpty())return;m_family=family;save();emit changed();}
void ThemeManager::setMode(const QString& mode) {if(mode==m_mode||(mode!="system"&&mode!="dark"&&mode!="light"))return;m_mode=mode;save();emit changed();}
void ThemeManager::save() {
    m_error.clear();
    const auto path=settingsPath();
    QJsonObject root;
    QFile previous(path);
    if(previous.exists()) {
        QJsonParseError parse;
        if(!previous.open(QIODevice::ReadOnly)||previous.size()>1024*1024){m_error="Preferences could not be read; theme applies for this session.";return;}
        const auto document=QJsonDocument::fromJson(previous.readAll(),&parse);
        if(parse.error!=QJsonParseError::NoError||!document.isObject()||document.object().value("schema").toInt()!=1){m_error="Unsupported preferences; theme applies for this session.";return;}
        root=document.object();
    }
    auto appearance=root.value("appearance").toObject();
    appearance["family"]=m_family;appearance["mode"]=m_mode;
    root["schema"]=1;root["appearance"]=appearance;
    if(!QDir().mkpath(QFileInfo(path).absolutePath())){m_error="Preferences folder could not be created.";return;}
    QSaveFile output(path);const auto bytes=QJsonDocument(root).toJson();
    if(!output.open(QIODevice::WriteOnly)||output.write(bytes)!=bytes.size()||!output.commit())m_error="Theme applies for this session; preferences could not be saved.";
}
