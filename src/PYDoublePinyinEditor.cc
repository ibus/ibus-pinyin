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
#include "PYDoublePinyinEditor.h"

#include "PYConfig.h"
#include "PYPinyinProperties.h"

namespace PY {

DoublePinyinEditor::DoublePinyinEditor (PinyinProperties & props, Config & config)
    : PinyinEditor (props, config)
{
    PhoneticEditor::setContext (PyZy::InputContext::DOUBLE_PINYIN);
}

DoublePinyinEditor::~DoublePinyinEditor ()
{
}

void
DoublePinyinEditor::updateAuxiliaryTextAfter (String &buffer)
{
    if (G_LIKELY (!m_config.doublePinyinShowRaw ()))
        return;

    if (m_text.empty ()) {
      return;
    }

    if (G_LIKELY (m_config.orientation () == IBUS_ORIENTATION_HORIZONTAL)) {
        buffer << "        [ ";
    }
    else {
        buffer << "\n[ ";
    }

    if (G_LIKELY (m_cursor == m_text.length ())) {
        buffer << m_text << " ]";
    }
    else {
        buffer.append (m_text.c_str (), m_cursor);
        buffer << " ";
        buffer.append (m_text.c_str () + m_cursor);
        buffer << " ]";
    }
}

gboolean
DoublePinyinEditor::processKeyEvent (guint keyval, guint keycode, guint modifiers)
{
    /* handle ';' key */
    if (G_UNLIKELY (keyval == IBUS_semicolon)) {
        if (cmshm_filter (modifiers) == 0) {
            if (insert (keyval))
                return TRUE;
        }
    }

    return PinyinEditor::processKeyEvent (keyval, keycode, modifiers);
}

};
