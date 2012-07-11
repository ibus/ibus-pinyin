/* vim:set et ts=4 sts=4:
 *
 * ibus-pinyin - The Chinese PinYin engine for IBus
 *
 * Copyright (c) 2008-2010 Peng Huang <shawn.p.huang@gmail.com>
 * Copyright (c) 2010 BYVoid <byvoid1@gmail.com>
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
#ifndef __PY_BOPOMOFO_EDITOR_H_
#define __PY_BOPOMOFO_EDITOR_H_

#include "PYPhoneticEditor.h"

namespace PY {

class Config;

class BopomofoEditor : public PhoneticEditor {

public:
    BopomofoEditor (PinyinProperties & props, Config & config);
    virtual ~BopomofoEditor (void);

protected:
    gboolean processGuideKey (guint keyval, guint keycode, guint modifiers);
    gboolean processAuxiliarySelectKey (guint keyval, guint keycode, guint modifiers);
    gboolean processSelectKey (guint keyval, guint keycode, guint modifiers);
    gboolean processBopomofo (guint keyval, guint keycode, guint modifiers);
    gboolean processKeyEvent (guint keyval, guint keycode, guint modifiers);

    void updateLookupTable ();
    void updateLookupTableFast ();
    void updateLookupTableLabel ();

    void reset ();

    gboolean m_select_mode;
};

};

#endif
