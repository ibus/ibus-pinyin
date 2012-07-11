/* vim:set et ts=4 sts=4:
 *
 * ibus-pinyin - The Chinese PinYin engine for IBus
 *
 * Copyright (c) 2008-2010 Peng Huang <shawn.p.huang@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <PyZy/InputContext.h>
#include <ibus.h>
#include <locale.h>
#include <stdlib.h>
#include <string>

#include "PYBus.h"
#include "PYConfig.h"
#include "PYEngine.h"
#include "PYPointer.h"

using namespace PY;

#define N_(text) text

static Pointer<IBusFactory> factory;

/* options */
static gboolean ibus = FALSE;
static gboolean verbose = FALSE;

static void
show_version_and_quit (void)
{
    g_print ("%s - Version %s\n", g_get_application_name (), VERSION);
    exit (EXIT_SUCCESS);
}

static const GOptionEntry entries[] =
{
    { "version", 'V', G_OPTION_FLAG_NO_ARG, G_OPTION_ARG_CALLBACK,
        (gpointer) show_version_and_quit, "Show the application's version.", NULL },
    { "ibus",    'i', 0, G_OPTION_ARG_NONE, &ibus, "component is executed by ibus", NULL },
    { "verbose", 'v', 0, G_OPTION_ARG_NONE, &verbose, "verbose", NULL },
    { NULL },
};


static void
ibus_disconnected_cb (IBusBus  *bus,
                      gpointer  user_data)
{
    g_debug ("bus disconnected");
    ibus_quit ();
}


static void
start_component (void)
{
    Pointer<IBusComponent> component;

    ibus_init ();
    Bus bus;

    if (!bus.isConnected ()) {
        g_warning ("Can not connect to ibus!");
        exit (0);
    }

    if (!ibus_bus_get_config (bus)) {
        g_warning ("IBus config component is not ready!");
        exit (0);
    }

    PinyinConfig::init (bus);
    BopomofoConfig::init (bus);
    {
      gchar *cache_dir =
          g_build_filename (g_get_user_cache_dir (), "ibus", "pinyin", NULL);
      gchar *config_dir =
          g_build_filename (g_get_user_config_dir (), "ibus", "pinyin", NULL);
      PyZy::InputContext::init (cache_dir, config_dir);
      g_free (cache_dir);
      g_free (config_dir);
    }

    g_signal_connect ((IBusBus *)bus, "disconnected", G_CALLBACK (ibus_disconnected_cb), NULL);

    component = ibus_component_new ("org.freedesktop.IBus.Pinyin",
                                    N_("Pinyin input method"),
                                    VERSION,
                                    "GPL",
                                    "Peng Huang <shawn.p.huang@gmail.com>",
                                    "http://code.google.com/p/ibus/",
                                    "",
                                    "ibus-pinyin");
    ibus_component_add_engine (component,
            ibus_engine_desc_new_varargs ("name", "pinyin-debug",
                                          "longname", N_("Pinyin (debug)"),
                                          "description", N_("Pinyin input method (debug)"),
                                          "language", "zh_CN",
                                          "license", "GPL",
                                          "author", "Peng Huang <shawn.p.huang@gmail.com>\n"
                                                    "BYVoid <byvoid1@gmail.com>",
                                          "icon", PKGDATADIR "/icons/ibus-pinyin.svg",
                                          "layout", "us",
                                          "symbol", "\u4e2d",
                                          NULL));
    ibus_component_add_engine (component,
            ibus_engine_desc_new_varargs ("name", "bopomofo-debug",
                                          "longname", N_("Bopomofo (debug)"),
                                          "description", N_("Bopomofo input method (debug)"),
                                          "language", "zh_CN",
                                          "license", "GPL",
                                          "author", "BYVoid <byvoid1@gmail.com>\n"
                                                    "Peng Huang <shawn.p.huang@gmail.com>",
                                          "icon", PKGDATADIR "/icons/ibus-bopomofo.svg",
                                          "layout", "us",
                                          "symbol", "\u4e2d",
                                          NULL));

    factory = ibus_factory_new (ibus_bus_get_connection (bus));

    if (ibus) {
        ibus_factory_add_engine (factory, "pinyin", IBUS_TYPE_PINYIN_ENGINE);
        ibus_factory_add_engine (factory, "bopomofo", IBUS_TYPE_PINYIN_ENGINE);
        ibus_bus_request_name (bus, "org.freedesktop.IBus.Pinyin", 0);
    }
    else {
        ibus_factory_add_engine (factory, "pinyin-debug", IBUS_TYPE_PINYIN_ENGINE);
        ibus_factory_add_engine (factory, "bopomofo-debug", IBUS_TYPE_PINYIN_ENGINE);
        ibus_bus_register_component (bus, component);
    }

    ibus_main ();
}

#include <signal.h>

static void
sigterm_cb (int sig)
{
    PyZy::InputContext::finalize ();
    ::exit (EXIT_FAILURE);
}

static void
atexit_cb (void)
{
    PyZy::InputContext::finalize ();
}

int
main (gint argc, gchar **argv)
{
    GError *error = NULL;
    GOptionContext *context;

    setlocale (LC_ALL, "");

    context = g_option_context_new ("- ibus pinyin engine component");

    g_option_context_add_main_entries (context, entries, "ibus-pinyin");

    if (!g_option_context_parse (context, &argc, &argv, &error)) {
        g_print ("Option parsing failed: %s\n", error->message);
        exit (-1);
    }

    ::signal (SIGTERM, sigterm_cb);
    ::signal (SIGINT, sigterm_cb);
    g_atexit (atexit_cb);

    start_component ();
    return 0;
}
