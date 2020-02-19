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
#include <QUrl>

SteamInputContext::SteamInputContext()
    : QPlatformInputContext()
{
    qDebug() << "Created a SteamInputContext!";
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
    QDesktopServices::openUrl(QUrl(QStringLiteral("steam://open/keyboard")));

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
