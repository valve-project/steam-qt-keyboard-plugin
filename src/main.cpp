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

#include <qpa/qplatforminputcontextplugin_p.h>

#include "steaminputcontext.h"

class SteamInputContextPlugin : public QPlatformInputContextPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QPlatformInputContextFactoryInterface_iid FILE "steaminputcontext.json")

public:
    QPlatformInputContext *create(const QString &id, const QStringList &args) override;

};

QPlatformInputContext *SteamInputContextPlugin::create(const QString &id, const QStringList &args)
{
    Q_UNUSED(args);

    if (id == QLatin1String("steam")) {
        return new SteamInputContext();
    }

    return nullptr;
}

#include "main.moc"
