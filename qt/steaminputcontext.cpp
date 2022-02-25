/*
 * Copyright 2020 Kai Uwe Broulik <kde@broulik.de>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "steaminputcontext.h"

#include <QDebug>
#include <QDesktopServices>
#include <QProcess>
#include <QUrl>
#include <QFileInfo>

#include <QDBusConnection>
#include <QDBusConnectionInterface>

static const auto dbusServiceName = QStringLiteral("org.freedesktop.portal.Steam");
static const auto dbusObjectName = QStringLiteral("/com/valvesoftware/Steam/Portal1");
static const auto dbusInterfaceName = QStringLiteral("com.valvesoftware.Steam.Portal1");

SteamInputContext::SteamInputContext()
    : QPlatformInputContext()
{
    m_steamWatcher = std::make_unique<QDBusServiceWatcher>(
        dbusServiceName,
        QDBusConnection::sessionBus(),
        QDBusServiceWatcher::WatchForOwnerChange
    );
    connect(m_steamWatcher.get(), &QDBusServiceWatcher::serviceRegistered, this, &SteamInputContext::onServiceRegistered);
    connect(m_steamWatcher.get(), &QDBusServiceWatcher::serviceUnregistered, this, &SteamInputContext::onServiceUnregistered);

    if (QDBusConnection::sessionBus().interface()->isServiceRegistered(dbusServiceName)) {
        onServiceRegistered();
    }
}

SteamInputContext::~SteamInputContext() = default;

bool SteamInputContext::isValid() const
{
    return true;
}

void SteamInputContext::showInputPanel()
{
    if (m_steamInterface) {
        m_steamInterface->asyncCall(QStringLiteral("OpenKeyboard"));
    }
}

void SteamInputContext::hideInputPanel()
{
    // TODO: Support hiding?
//     if (m_steamInterface) {
//         m_steamInterface->asyncCall(QStringLiteral("CloseKeyboard"));
//     }
}

bool SteamInputContext::isInputPanelVisible() const
{
    if (!m_steamInterface) {
        return false;
    } else {
        return m_visible;
    }
}

void SteamInputContext::onServiceRegistered()
{
    //TODO: Use generated interface class
    m_steamInterface = std::make_unique<QDBusInterface>(
        dbusServiceName,
        dbusObjectName,
        dbusInterfaceName,
        QDBusConnection::sessionBus()
    );

    //TODO: It would probably be good to have this so we can satisfy the full
    //      InputContext API.
    //connect(m_steamInterface.get(), &SteamInterface::keyboardVisibleChanged, this, onKeyboardVisibleChanged);
}

void SteamInputContext::onServiceUnregistered()
{
    m_steamInterface.reset();
}
