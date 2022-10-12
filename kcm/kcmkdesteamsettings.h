/*  This file is part of the KDE's Plasma desktop
    SPDX-FileCopyrightText: 2022 ivan tkachenko <me@ratijas.tk>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <KCModule>
#include <KConfigGroup>
#include <KSharedConfig>
#include <memory>

namespace Ui
{
class KCMKdeSteamSettingsWidget;
}

namespace KdeSteamSettings
{
class KeyboardSettings;
}

/**
 * @short A KCM to configure Plasma QtQuick settings
 */
class KCMKdeSteamSettingsModule : public KCModule
{
    Q_OBJECT

public:
    explicit KCMKdeSteamSettingsModule(QWidget *parent, const QVariantList &);
    ~KCMKdeSteamSettingsModule() override;

private:
    std::unique_ptr<Ui::KCMKdeSteamSettingsWidget> m_ui;
    std::unique_ptr<KdeSteamSettings::KeyboardSettings> m_settings;
};
