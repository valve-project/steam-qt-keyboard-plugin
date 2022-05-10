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

#include <qpa/qplatforminputcontext.h>

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

    Q_SLOT void onEnabledChanged(bool enabled);

private:
    bool m_visible = false;
    bool m_enabled = true;
    QString m_steamExecutable;
};
