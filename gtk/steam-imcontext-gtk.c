/*
 * Copyright (C) 2010, Intel Corporation.
 * Copyright (C) 2012 One Laptop per Child Association
 * Copyright (C) 2012 Canonical Ltd
 * Copyright (C) 2022 Arjen Hiemstra <ahiemstra@heimr.nl>
 *
 * Author: Raymond Liu <raymond.liu@intel.com>
 *
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


#include <gdk/gdk.h>

#include "steam-imcontext-gtk.h"

static GType _steam_im_context_type = 0;
static GtkIMContextClass *parent_class = NULL;

static void steam_im_context_finalize(GObject *object);
static void steam_im_context_class_init(SteamIMContextClass *klass, gpointer class_data);
static void steam_im_context_init(SteamIMContext *steam_im_context, GTypeClass *g_class);

static void steam_im_context_focus_in(GtkIMContext *context);
static gboolean steam_im_context_filter_keypress(GtkIMContext *, GdkEventKey *);

GType steam_im_context_get_type()
{
    return _steam_im_context_type;
}

void steam_im_context_register_type(GTypeModule *type_module)
{
    static const GTypeInfo steam_im_context_info = {
        sizeof(SteamIMContextClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) steam_im_context_class_init,
        NULL,
        NULL,
        sizeof(SteamIMContext),
        0,
        (GInstanceInitFunc) steam_im_context_init,
        NULL
    };

    if (_steam_im_context_type)
        return;

    _steam_im_context_type = g_type_module_register_type(type_module, GTK_TYPE_IM_CONTEXT, "SteamIMContext", &steam_im_context_info, (GTypeFlags)0);
}

GtkIMContext *steam_im_context_new(void)
{
    SteamIMContext *ic = STEAM_IM_CONTEXT(g_object_new(STEAM_TYPE_IM_CONTEXT, NULL));
    return GTK_IM_CONTEXT(ic);
}

static void steam_im_context_dispose(GObject *object)
{
    SteamIMContext *im_context = STEAM_IM_CONTEXT(object);
    g_free(im_context->steamExecutable);
    G_OBJECT_CLASS(parent_class)->dispose(object);
}

static void steam_im_context_finalize(GObject *object)
{
    G_OBJECT_CLASS(parent_class)->finalize(object);
}

static void steam_im_context_class_init(SteamIMContextClass *klass, gpointer class_data)
{
    (void)class_data;

    GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
    parent_class = (GtkIMContextClass *)g_type_class_peek_parent(klass);
    GtkIMContextClass *imclass = GTK_IM_CONTEXT_CLASS(klass);

    gobject_class->dispose = steam_im_context_dispose;
    gobject_class->finalize = steam_im_context_finalize;

    imclass->focus_in = steam_im_context_focus_in;
    imclass->filter_keypress = steam_im_context_filter_keypress;
}

static void steam_im_context_init(SteamIMContext *self, GTypeClass *g_class)
{
    (void)g_class;

    const gchar* steamRuntime = g_environ_getenv(NULL, "STEAM_RUNTIME");
    if (steamRuntime) {
        gchar* dirName = g_path_get_dirname(steamRuntime);
        self->steamExecutable = g_strconcat(dirName, "/steam", NULL);
        g_free(dirName);
    } else {
        self->steamExecutable = g_strdup("steam");
    }
}

static void steam_im_context_focus_in(GtkIMContext *context)
{
    SteamIMContext *im_context = STEAM_IM_CONTEXT(context);
    GError *error = NULL;

    gchar* argv[4];
    argv[0] = im_context->steamExecutable;
    argv[1] = (gchar*)"-if-running";
    argv[2] = (gchar*)"steam://open/keyboard";
    argv[3] = NULL;

    if (!g_spawn_async(NULL, argv, NULL, G_SPAWN_SEARCH_PATH, NULL, NULL, NULL, &error)) {
        g_warning("Error opening Steam keyboard: %s", error->message);
    }
}

static gboolean steam_im_context_filter_keypress(GtkIMContext *context, GdkEventKey *event)
{
    SteamIMContext *im_context = STEAM_IM_CONTEXT(context);

    if (event->type == GDK_KEY_RELEASE) {
        gunichar ch = gdk_keyval_to_unicode (event->keyval);
        if (ch != 0 && !g_unichar_iscntrl (ch)) {
            gchar keyval_utf8[7];
            gint length = g_unichar_to_utf8(gdk_keyval_to_unicode(event->keyval), keyval_utf8);
            keyval_utf8[length] = '\0';
            g_signal_emit_by_name(im_context, "commit", keyval_utf8);
            return TRUE;
        }
    }
    return FALSE;
}

