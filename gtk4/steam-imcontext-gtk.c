/* SPDX-License-Identifier: LGPL-2.1-or-later
 * SPDX-FileCopyrightText: 2010, Intel Corporation.
 * SPDX-FileCopyrightText: 2012 One Laptop per Child Association
 * SPDX-FileCopyrightText: 2012 Canonical Ltd
 * SPDX-FileCopyrightText: 2022 Arjen Hiemstra <ahiemstra@heimr.nl>
 * SPDX-FileCopyrightText: 2024 Igalia
 *
 * Author: Raymond Liu <raymond.liu@intel.com>
 */

#include "steam-imcontext-gtk.h"

#include <gtk/gtkimmodule.h>

struct _SteamIMContext
{
  GtkIMContext parent_instance;

  char *steamExecutable;
};

G_DEFINE_DYNAMIC_TYPE(SteamIMContext, steam_im_context, GTK_TYPE_IM_CONTEXT)

/* {{{ GIOExtension point boilerplate */
void g_io_module_load(GIOModule *module)
{
    g_type_module_use((GTypeModule*) module);

    steam_im_context_register_type((GTypeModule*) module);

    g_io_extension_point_implement(GTK_IM_MODULE_EXTENSION_POINT_NAME,
                                   STEAM_TYPE_IM_CONTEXT,
                                   "Steam",
                                   50);
}

void g_io_module_unload(GIOModule *module)
{
    g_type_module_unuse ((GTypeModule*) module);
}

char** g_io_module_query(void)
{
    static const char *eps[] = {
        GTK_IM_MODULE_EXTENSION_POINT_NAME,
        NULL,
    };

    return g_strdupv ((char**) eps);
}
/* }}} */

/* {{{ GtkIMContext implementation */
static void steam_im_context_focus_in(GtkIMContext *context)
{
    SteamIMContext *im_context = STEAM_IM_CONTEXT(context);
    GError *error = NULL;

    char* argv[4];
    argv[0] = im_context->steamExecutable;
    argv[1] = (char*)"-if-running";
    argv[2] = (char*)"steam://open/keyboard";
    argv[3] = NULL;

    if (!g_spawn_async(NULL, argv, NULL, G_SPAWN_SEARCH_PATH, NULL, NULL, NULL, &error)) {
        g_warning("Error opening Steam keyboard: %s", error->message);
    }
}

static gboolean steam_im_context_filter_keypress(GtkIMContext *context, GdkEvent *event)
{
    if (gdk_event_get_event_type(event) == GDK_KEY_RELEASE) {
        int keyval = gdk_key_event_get_keyval(event);
        gunichar ch = gdk_keyval_to_unicode(keyval);
        if (ch != 0 && !g_unichar_iscntrl(ch)) {
            char buf[8] = { 0, };
            g_unichar_to_utf8(ch, buf);
            g_signal_emit_by_name (context, "commit", buf);
            return TRUE;
        }
    }
    return FALSE;
}
/* }}} */

/* {{{ GObject implementation */
static void steam_im_context_finalize(GObject *object)
{
    SteamIMContext *im_context = STEAM_IM_CONTEXT(object);
    g_free(im_context->steamExecutable);
    G_OBJECT_CLASS(steam_im_context_parent_class)->finalize(object);
}

static void steam_im_context_class_finalize(SteamIMContextClass *klass G_GNUC_UNUSED)
{
}

static void steam_im_context_class_init(SteamIMContextClass *klass)
{
    GtkIMContextClass *imclass = GTK_IM_CONTEXT_CLASS(klass);

    steam_im_context_parent_class = (GtkIMContextClass*) g_type_class_peek_parent(klass);

    G_OBJECT_CLASS(klass)->finalize = steam_im_context_finalize;

    imclass->filter_keypress = steam_im_context_filter_keypress;
    imclass->focus_in = steam_im_context_focus_in;
}

static void steam_im_context_init(SteamIMContext *self)
{
    const gchar* steamRuntime = g_environ_getenv(NULL, "STEAM_RUNTIME");
    if (steamRuntime) {
        gchar* dirName = g_path_get_dirname(steamRuntime);
        self->steamExecutable = g_strconcat(dirName, "/steam", NULL);
        g_free(dirName);
    } else {
        self->steamExecutable = g_strdup("steam");
    }
}
/* }}} */

GtkIMContext *steam_im_context_new(void)
{
    SteamIMContext *ic = STEAM_IM_CONTEXT(g_object_new(STEAM_TYPE_IM_CONTEXT, NULL));
    return GTK_IM_CONTEXT(ic);
}
