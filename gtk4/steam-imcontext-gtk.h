/* SPDX-License-Identifier: LGPL-2.1-or-later
 * SPDX-FileCopyrightText: 2024 Igalia
 */

#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define STEAM_TYPE_IM_CONTEXT (steam_im_context_get_type())

G_DECLARE_FINAL_TYPE(SteamIMContext, steam_im_context, STEAM, IM_CONTEXT, GtkIMContext)

G_END_DECLS
