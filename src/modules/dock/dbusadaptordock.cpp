/*
 * Copyright (C) 2021 ~ 2022 Deepin Technology Co., Ltd.
 *
 * Author:     weizhixiang <weizhixiang@uniontech.com>
 *
 * Maintainer: weizhixiang <weizhixiang@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "dbusadaptordock.h"

DBusAdaptorDock::DBusAdaptorDock(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);

    Dock *dock = static_cast<Dock *>(QObject::parent());
    if (dock) {
        connect(dock, &Dock::serviceRestarted, this, [&] {
            Q_EMIT ServiceRestarted();});
        connect(dock, &Dock::entryAdded, this, [&](QString entryObjPath, int32_t index){
            Q_EMIT EntryAdded(QDBusObjectPath(entryObjPath), index);});
        connect(dock, &Dock::entryRemoved, this, &DBusAdaptorDock::EntryRemoved);
        connect(dock, &Dock::hideStateChanged, this, &DBusAdaptorDock::HideStateChanged);
        connect(dock, &Dock::frontendWindowRectChanged, this, &DBusAdaptorDock::FrontendWindowRectChanged);
    }
}

DBusAdaptorDock::~DBusAdaptorDock()
{
    // destructor
}

int DBusAdaptorDock::displayMode() const
{
    return parent()->getDisplayMode();
}

void DBusAdaptorDock::setDisplayMode(int value)
{
    if (displayMode() != value) {
        parent()->setDisplayMode(value);
        Q_EMIT DisplayModeChanged(value);
    }
}

QStringList DBusAdaptorDock::dockedApps() const
{
    return parent()->getDockedApps();
}

QList<QDBusObjectPath> DBusAdaptorDock::entries() const
{
    QList<QDBusObjectPath> ret;
    for (auto path : parent()->getEntryPaths())
        ret.push_back(QDBusObjectPath(path));
    return ret;
}

int DBusAdaptorDock::hideMode() const
{
    return int(parent()->getHideMode());
}

void DBusAdaptorDock::setHideMode(int value)
{
    if (hideMode() != value) {
        parent()->setHideMode(static_cast<HideMode>(value));
        Q_EMIT HideModeChanged(value);
    }
}

int DBusAdaptorDock::hideState() const
{
    return int(parent()->getHideState());
}

uint DBusAdaptorDock::hideTimeout() const
{
    return parent()->getHideTimeout();
}

void DBusAdaptorDock::setHideTimeout(uint value)
{
    if (hideTimeout() != value) {
        parent()->setHideTimeout(value);
        Q_EMIT HideTimeoutChanged(value);
    }
}

uint DBusAdaptorDock::windowSizeEfficient() const
{
    return parent()->getWindowSizeEfficient();
}

void DBusAdaptorDock::setWindowSizeEfficient(uint value)
{
    if (windowSizeEfficient() != value) {
        parent()->setWindowSizeEfficient(value);
        Q_EMIT WindowSizeEfficientChanged(value);
    }
}

uint DBusAdaptorDock::windowSizeFashion() const
{
    return parent()->getWindowSizeFashion();
}

void DBusAdaptorDock::setWindowSizeFashion(uint value)
{
    if (windowSizeFashion() != value) {
        parent()->setWindowSizeFashion(value);
        Q_EMIT WindowSizeFashionChanged(value);
    }
}

QRect DBusAdaptorDock::frontendWindowRect() const
{
    return parent()->getFrontendWindowRect();
}

double DBusAdaptorDock::opacity() const
{
    return parent()->getOpacity();
}

uint DBusAdaptorDock::iconSize() const
{
    return parent()->getIconSize();
}

void DBusAdaptorDock::setIconSize(uint value)
{
    if (iconSize() != value) {
        parent()->setIconSize(value);
        Q_EMIT IconSizeChanged(value);
    }
}

int DBusAdaptorDock::position() const
{
    return parent()->getPosition();
}

void DBusAdaptorDock::setPosition(int value)
{
    if (position() != value) {
        parent()->setPosition(value);
        Q_EMIT PositionChanged(value);
    }
}

uint DBusAdaptorDock::showTimeout() const
{
    return parent()->getShowTimeout();
}

void DBusAdaptorDock::setShowTimeout(uint value)
{
    if (showTimeout() != value) {
        parent()->setShowTimeout(value);
        Q_EMIT ShowTimeoutChanged(value);
    }
}

Dock *DBusAdaptorDock::parent() const
{
    return static_cast<Dock *>(QObject::parent());
}

void DBusAdaptorDock::CloseWindow(uint win)
{
    parent()->closeWindow(win);
}

// for debug
QStringList DBusAdaptorDock::GetEntryIDs()
{
    return parent()->getEntryIDs();
}

bool DBusAdaptorDock::IsDocked(const QString &desktopFile)
{
    return parent()->isDocked(desktopFile);
}

bool DBusAdaptorDock::IsOnDock(const QString &desktopFile)
{
    return parent()->isOnDock(desktopFile);
}

void DBusAdaptorDock::MoveEntry(int index, int newIndex)
{
    parent()->moveEntry(index, newIndex);
}

QString DBusAdaptorDock::QueryWindowIdentifyMethod(uint win)
{
    return parent()->queryWindowIdentifyMethod(win);
}

QStringList DBusAdaptorDock::GetDockedAppsDesktopFiles()
{
    return parent()->getDockedAppsDesktopFiles();
}

QString DBusAdaptorDock::GetPluginSettings()
{
    return parent()->getPluginSettings();
}

void DBusAdaptorDock::SetPluginSettings(QString jsonStr)
{
    parent()->setPluginSettings(jsonStr);
}

void DBusAdaptorDock::MergePluginSettings(QString jsonStr)
{
    parent()->mergePluginSettings(jsonStr);
}

void DBusAdaptorDock::RemovePluginSettings(QString key1, QStringList key2List)
{
    parent()->removePluginSettings(key1, key2List);
}

bool DBusAdaptorDock::RequestDock(const QString &desktopFile, int index)
{
    return parent()->requestDock(desktopFile, index);
}

bool DBusAdaptorDock::RequestUndock(const QString &desktopFile)
{
    return parent()->requestUndock(desktopFile);
}

void DBusAdaptorDock::SetFrontendWindowRect(int x, int y, uint width, uint height)
{
    parent()->setFrontendWindowRect(x, y, width, height);
}

