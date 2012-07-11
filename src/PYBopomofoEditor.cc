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
#include "PYBopomofoEditor.h"

#include <cstring>

#include "PYConfig.h"
#include "PYPinyinProperties.h"

namespace PY {

const static gchar * bopomofo_select_keys[] = {
    "1234567890",
    "asdfghjkl;",
    "1qaz2wsxed",
    "asdfzxcvgb",
    "1234qweras",
    "aoeu;qjkix",
    "aoeuhtnsid",
    "aoeuidhtns",
    "qweasdzxcr"
};

BopomofoEditor::BopomofoEditor (PinyinProperties & props, Config & config)
    : PhoneticEditor (props, config),
      m_select_mode (FALSE)
{
    PhoneticEditor::setContext (PyZy::InputContext::BOPOMOFO);
}

BopomofoEditor::~BopomofoEditor (void)
{
}

void
BopomofoEditor::reset (void)
{
    m_select_mode = FALSE;
    PhoneticEditor::reset ();
}

gboolean
BopomofoEditor::processGuideKey (guint keyval, guint keycode, guint modifiers)
{
    if (!m_config.guideKey ())
        return FALSE;

    if (G_UNLIKELY (cmshm_filter (modifiers) != 0))
        return FALSE;

    if (G_LIKELY (m_select_mode))
        return FALSE;

    if (G_UNLIKELY (keyval == IBUS_space)) {
        m_select_mode = TRUE;
        updateLookupTable ();
        return TRUE;
    }

    return FALSE;
}

gboolean
BopomofoEditor::processAuxiliarySelectKey (guint keyval, guint keycode, guint modifiers)
{
    if (G_UNLIKELY (cmshm_filter (modifiers) != 0))
        return FALSE;

    guint i;

    switch (keyval) {
    case IBUS_KP_0:
        i = 9;
        if (!m_config.auxiliarySelectKeyKP ())
            return FALSE;
        break;
    case IBUS_KP_1 ... IBUS_KP_9:
        i = keyval - IBUS_KP_1;
        if (!m_config.auxiliarySelectKeyKP ())
            return FALSE;
        break;
    case IBUS_F1 ... IBUS_F10:
        i = keyval - IBUS_F1;
        if (!m_config.auxiliarySelectKeyF ())
            return FALSE;
        break;
    default:
        return FALSE;
    }

    m_select_mode = TRUE;
    selectCandidateInPage (i);

    return TRUE;
}

gboolean
BopomofoEditor::processSelectKey (guint keyval, guint keycode, guint modifiers)
{
    if (G_UNLIKELY (m_text.empty ()))
        return FALSE;

    if (G_LIKELY (!m_select_mode && ((modifiers & IBUS_MOD1_MASK) == 0)))
        return FALSE;

    const gchar * pos =
        std::strchr (bopomofo_select_keys[m_config.selectKeys ()], keyval);
    if (pos == NULL)
        return FALSE;

    m_select_mode = TRUE;

    guint i = pos - bopomofo_select_keys[m_config.selectKeys ()];
    selectCandidateInPage (i);

    return TRUE;
}

gboolean
BopomofoEditor::processBopomofo (guint keyval, guint keycode, guint modifiers)
{
    if (G_UNLIKELY (cmshm_filter (modifiers) != 0))
        return !m_text.empty() ? TRUE : FALSE;

    const bool ret = insert (keyval);
    if (ret) {
      m_select_mode = FALSE;
    }
    return ret;
}

gboolean
BopomofoEditor::processKeyEvent (guint keyval, guint keycode, guint modifiers)
{
    modifiers &= (IBUS_SHIFT_MASK |
                  IBUS_CONTROL_MASK |
                  IBUS_MOD1_MASK |
                  IBUS_SUPER_MASK |
                  IBUS_HYPER_MASK |
                  IBUS_META_MASK |
                  IBUS_LOCK_MASK);


    if (G_UNLIKELY (processGuideKey (keyval, keycode, modifiers)))
        return TRUE;
    if (G_UNLIKELY (processSelectKey (keyval, keycode, modifiers) == TRUE))
        return TRUE;
    if (G_UNLIKELY (processAuxiliarySelectKey (keyval, keycode, modifiers)))
        return TRUE;
    if (G_UNLIKELY (processBopomofo (keyval, keycode ,modifiers)))
        return TRUE;

    switch (keyval) {
    case IBUS_space:
        m_select_mode = TRUE;
        return processSpace (keyval, keycode, modifiers);

    case IBUS_Up:
    case IBUS_KP_Up:
    case IBUS_Down:
    case IBUS_KP_Down:
    case IBUS_Page_Up:
    case IBUS_KP_Page_Up:
    case IBUS_Page_Down:
    case IBUS_KP_Page_Down:
    case IBUS_Tab:
        m_select_mode = TRUE;
        return PhoneticEditor::processFunctionKey (keyval, keycode, modifiers);

    case IBUS_BackSpace:
    case IBUS_Delete:
    case IBUS_KP_Delete:
    case IBUS_Left:
    case IBUS_KP_Left:
    case IBUS_Right:
    case IBUS_KP_Right:
    case IBUS_Home:
    case IBUS_KP_Home:
    case IBUS_End:
    case IBUS_KP_End:
        m_select_mode = FALSE;
        return PhoneticEditor::processFunctionKey (keyval, keycode, modifiers);

    default:
        return PhoneticEditor::processFunctionKey (keyval, keycode, modifiers);
    }

}

void
BopomofoEditor::updateLookupTableLabel ()
{
    std::string str;
    guint color = m_select_mode ? 0x000000 : 0xBBBBBB;
    for (const gchar *p = bopomofo_select_keys[m_config.selectKeys ()]; *p; p++)
    {
        guint i = p - bopomofo_select_keys[m_config.selectKeys ()];
        if (i >= m_config.pageSize ())
            break;
        str = *p;
        str += ".";
        Text text_label (str);
        text_label.appendAttribute (IBUS_ATTR_TYPE_FOREGROUND, color, 0, -1);
        m_lookup_table.setLabel (i, text_label);
    }
    if (m_config.guideKey ())
        m_lookup_table.setCursorVisable (m_select_mode);
    else
        m_lookup_table.setCursorVisable (TRUE);
}

void
BopomofoEditor::updateLookupTableFast ()
{
    updateLookupTableLabel ();
    PhoneticEditor::updateLookupTableFast ();
}

void
BopomofoEditor::updateLookupTable ()
{
    m_lookup_table.setPageSize (m_config.pageSize ());
    m_lookup_table.setOrientation (m_config.orientation ());
    updateLookupTableLabel ();
    PhoneticEditor::updateLookupTable ();
}

};
