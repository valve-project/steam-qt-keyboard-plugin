/*
 * Copyright (C) 2010, Intel Corporation.
 * Copyright (C) 2022 Arjen Hiemstra <ahiemstra@heimr.nl>
 *
 * Author: Raymond Liu <raymond.liu@intel.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 */

#ifndef _STEAM_IMCONTEXT_GTK_H
#define _STEAM_IMCONTEXT_GTK_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

typedef struct _SteamIMContext SteamIMContext;
typedef struct _SteamIMContextClass SteamIMContextClass;

struct _SteamIMContext {
    GtkIMContext parent;
    gchar* steamExecutable;
    GDBusProxy *keyboardService;
    gboolean enabled;
};

struct _SteamIMContextClass {
    GtkIMContextClass parent;
};

#define STEAM_TYPE_IM_CONTEXT            (steam_im_context_get_type())
#define STEAM_IM_CONTEXT(obj)            (G_TYPE_CHECK_INSTANCE_CAST((obj), STEAM_TYPE_IM_CONTEXT, SteamIMContext))

GType steam_im_context_get_type(void);
void steam_im_context_register_type(GTypeModule *type_module);
GtkIMContext *steam_im_context_new(void);

G_END_DECLS

#endif //_STEAM_IMCONTEXT_GTK_H
