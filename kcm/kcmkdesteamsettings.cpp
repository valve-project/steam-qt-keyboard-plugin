/*  This file is part of the KDE's Plasma desktop
    SPDX-FileCopyrightText: 2022 ivan tkachenko <me@ratijas.tk>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kcmkdesteamsettings.h"

#include <KAboutData>
#include <KPluginFactory>
#include <QDebug>

#include "kdesteamsettings.h"
#include "ui_kcmkdesteamsettingswidget.h"

K_PLUGIN_CLASS_WITH_JSON(KCMKdeSteamSettingsModule, "kcm_kdesteamsettings.json")

KCMKdeSteamSettingsModule::KCMKdeSteamSettingsModule(QWidget *parent, const QVariantList &args)
    : KCModule(parent, args)
    , m_ui(new Ui::KCMKdeSteamSettingsWidget)
    , m_settings(new KdeSteamSettings::KeyboardSettings(KSharedConfig::openConfig(QStringLiteral("kdesteam"))))
{
    KAboutData *about = new KAboutData(QStringLiteral("Steam Settings for KDE"),
                                       i18n("Steam Settings for KDE"),
                                       QString(),
                                       i18n("Configure Steam Settings"),
                                       KAboutLicense::GPL);
    about->addAuthor(i18n("ivan tkachenko"), i18n("Maintainer"), QStringLiteral("me@ratijas.tk"));
    setAboutData(about);

    m_ui->setupUi(this);
    addConfig(m_settings.get(), this);
}

KCMKdeSteamSettingsModule::~KCMKdeSteamSettingsModule()
{
}

#include "kcmkdesteamsettings.moc"
