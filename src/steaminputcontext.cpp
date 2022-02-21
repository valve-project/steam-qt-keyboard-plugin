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

SteamInputContext::SteamInputContext()
    : QPlatformInputContext()
{
    qDebug() << "Created a SteamInputContext!";

    auto steamRuntime = qEnvironmentVariable("STEAM_RUNTIME");
    if (!steamRuntime.isEmpty()) {
        auto dirName = QFileInfo(steamRuntime).absolutePath();
        dirName.append(QStringLiteral("/steam"));
        m_steamExecutable = dirName;
    } else {
        m_steamExecutable = QStringLiteral("steam");
    }
}

SteamInputContext::~SteamInputContext() = default;

bool SteamInputContext::isValid() const
{
    return true;
}

void SteamInputContext::showInputPanel()
{
    qDebug() << "Show input panel";

    // Ask steam to open the keyboard
    // This does a "proper" run, including bouncy startup cursor
    //QDesktopServices::openUrl(QUrl(QStringLiteral("steam://open/keyboard")));
    // which we don't really want in this case, run it directly instead
    QProcess::startDetached(m_steamExecutable, {QStringLiteral("-ifrunning"), QStringLiteral("steam://open/keyboard")});

    // Ideally we then told it the keyboard became visible now
}

void SteamInputContext::hideInputPanel()
{
    qDebug() << "Hide input panel";

    // Ideally this closed the keyboard again
}

bool SteamInputContext::isInputPanelVisible() const
{
    // Ideally this returned whether the Steam keyboard is actually shown right now
    return false;
}
