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

#pragma once

#include <memory>

#include <qpa/qplatforminputcontext.h>

#include <QDBusServiceWatcher>
#include <QDBusInterface>

class SteamInputContext : public QPlatformInputContext
{
    Q_OBJECT

public:
    SteamInputContext();
    ~SteamInputContext() override;

    bool isValid() const override;

    void showInputPanel() override;
    void hideInputPanel() override;
    bool isInputPanelVisible() const override;

private:
    void onServiceRegistered();
    void onServiceUnregistered();

    bool m_visible = false;
    std::unique_ptr<QDBusServiceWatcher> m_steamWatcher;
    std::unique_ptr<QDBusInterface> m_steamInterface;
};
