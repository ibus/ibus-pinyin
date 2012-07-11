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
#include "PYPhoneticEditor.h"

#include <cctype>

#include "PYConfig.h"
#include "PYHalfFullConverter.h"
#include "PYPinyinProperties.h"

namespace PY {

/* init static members */
PhoneticEditor::PhoneticEditor (PinyinProperties & props, Config & config)
    : Editor (props, config),
      m_observer (PinyinObserver(*this)),
      m_lookup_table (m_config.pageSize ())
{
}

PhoneticEditor::~PhoneticEditor ()
{
    unsetContext ();
}

void
PhoneticEditor::setContext (PyZy::InputContext::InputType type)
{
    if (m_context.get () != NULL)
        unsetContext ();

    m_context.reset (PyZy::InputContext::create (type, &m_observer));
    m_config.addContext (m_context.get ());
    m_props.setContext (m_context.get ());
}

void
PhoneticEditor::unsetContext ()
{
    if (m_context.get () == NULL)
        return;

    m_config.removeContext (m_context.get ());
    m_props.clearContext ();
    m_context.reset ();
}

gboolean
PhoneticEditor::processSpace (guint keyval, guint keycode, guint modifiers)
{
    if (m_text.empty ())
        return FALSE;
    if (cmshm_filter (modifiers) != 0)
        return TRUE;
    if (m_lookup_table.size () != 0) {
        selectCandidate (m_lookup_table.cursorPos ());
    }
    else {
        commit ();
    }
    return TRUE;
}

gboolean
PhoneticEditor::processFunctionKey (guint keyval, guint keycode, guint modifiers)
{
    if (m_text.empty ())
        return FALSE;

    /* ignore numlock */
    modifiers = cmshm_filter (modifiers);

    if (modifiers != 0 && modifiers != IBUS_CONTROL_MASK)
        return TRUE;

    /* process some cursor control keys */
    if (modifiers == 0) {
        switch (keyval) {
        case IBUS_Return:
        case IBUS_KP_Enter:
            commit();
            return TRUE;

        case IBUS_BackSpace:
            if (!unselectCandidates ()) {
                removeCharBefore ();
            }
            return TRUE;

        case IBUS_Delete:
        case IBUS_KP_Delete:
            removeCharAfter ();
            return TRUE;

        case IBUS_Left:
        case IBUS_KP_Left:
            if (!unselectCandidates ()) {
                moveCursorLeft ();
            }
            return TRUE;

        case IBUS_Right:
        case IBUS_KP_Right:
            if (!unselectCandidates ()) {
                moveCursorRight ();
            }
            return TRUE;

        case IBUS_Home:
        case IBUS_KP_Home:
            if (!unselectCandidates ()) {
                moveCursorToBegin ();
            }
            return TRUE;

        case IBUS_End:
        case IBUS_KP_End:
            if (!unselectCandidates ()) {
                moveCursorToEnd ();
            }
            return TRUE;

        case IBUS_Up:
        case IBUS_KP_Up:
            cursorUp ();
            return TRUE;

        case IBUS_Down:
        case IBUS_KP_Down:
            cursorDown ();
            return TRUE;

        case IBUS_Page_Up:
        case IBUS_KP_Page_Up:
            pageUp ();
            return TRUE;

        case IBUS_Page_Down:
        case IBUS_KP_Page_Down:
        case IBUS_Tab:
            pageDown ();
            return TRUE;

        case IBUS_Escape:
            reset ();
            return TRUE;
        default:
            return TRUE;
        }
    }
    else {
        switch (keyval) {
        case IBUS_BackSpace:
            if (!unselectCandidates ()) {
                removeWordBefore ();
            }
            return TRUE;

        case IBUS_Delete:
        case IBUS_KP_Delete:
            removeWordAfter ();
            return TRUE;

        case IBUS_Left:
        case IBUS_KP_Left:
            if (!unselectCandidates ()) {
                moveCursorLeftByWord ();
            }
            return TRUE;

        case IBUS_Right:
        case IBUS_KP_Right:
            if (!unselectCandidates ()) {
                moveCursorToEnd ();
            }
            return TRUE;

        default:
            return TRUE;
        };
    }
    return TRUE;
}

gboolean
PhoneticEditor::processKeyEvent (guint keyval, guint keycode, guint modifiers)
{
    return FALSE;
}

void
PhoneticEditor::updateLookupTableFast (void)
{
    Editor::updateLookupTableFast (m_lookup_table, TRUE);
}

void
PhoneticEditor::updateLookupTable (void)
{
    m_lookup_table.clear ();

    fillLookupTableByPage ();
    if (m_lookup_table.size ()) {
        Editor::updateLookupTable (m_lookup_table, TRUE);
    }
    else {
        hideLookupTable ();
    }
}

gboolean
PhoneticEditor::fillLookupTableByPage (void)
{
    const guint filled_nr = m_lookup_table.size ();
    const guint page_size = m_lookup_table.pageSize ();

    if (!m_context->hasCandidate (filled_nr))
        return FALSE;

    for (guint i = filled_nr; i < filled_nr + page_size; i++) {
        PyZy::Candidate candidate;
        if (!m_context->getCandidate (i, candidate)) {
            break;
        }

        Text text (candidate.text);
        switch (candidate.type) {
        case PyZy::USER_PHRASE:
            text.appendAttribute (IBUS_ATTR_TYPE_FOREGROUND, 0x000000ef, 0, -1);
            break;
        case PyZy::SPECIAL_PHRASE:
            text.appendAttribute (IBUS_ATTR_TYPE_FOREGROUND, 0x0000ef00, 0, -1);
            break;
        default:
            break;
        }
        m_lookup_table.appendCandidate (text);
    }

    return TRUE;
}

gboolean
PhoneticEditor::insert (gint ch)
{
    if (!isascii(ch)) {
        return false;
    }
    return m_context->insert (ch);
}

gboolean
PhoneticEditor::removeCharBefore (void)
{
    return m_context->removeCharBefore ();
}

gboolean
PhoneticEditor::removeCharAfter (void)
{
    return m_context->removeCharAfter ();
}

gboolean
PhoneticEditor::removeWordBefore (void)
{
    return m_context->removeWordBefore ();
}

gboolean
PhoneticEditor::removeWordAfter (void)
{
    return m_context->removeWordAfter ();
}

gboolean
PhoneticEditor::moveCursorLeft (void)
{
    return m_context->moveCursorLeft ();
}

gboolean
PhoneticEditor::moveCursorRight (void)
{
    return m_context->moveCursorRight ();
}

gboolean
PhoneticEditor::moveCursorLeftByWord (void)
{
    return m_context->moveCursorLeftByWord ();
}

gboolean
PhoneticEditor::moveCursorRightByWord (void)
{
    return m_context->moveCursorRightByWord ();
}

gboolean
PhoneticEditor::moveCursorToBegin (void)
{
    return m_context->moveCursorToBegin ();
}

gboolean
PhoneticEditor::moveCursorToEnd (void)
{
    return m_context->moveCursorToEnd ();
}

void
PhoneticEditor::pageUp (void)
{
    if (G_LIKELY (m_lookup_table.pageUp ())) {
        updateLookupTableFast ();
    }
}

void
PhoneticEditor::pageDown (void)
{
    if (G_LIKELY(
            (m_lookup_table.pageDown ()) ||
            (fillLookupTableByPage () && m_lookup_table.pageDown ()))) {
        updateLookupTableFast ();
    }
}

void
PhoneticEditor::cursorUp (void)
{
    if (G_LIKELY (m_lookup_table.cursorUp ())) {
        updateLookupTableFast ();
    }
}

void
PhoneticEditor::cursorDown (void)
{
    if (G_LIKELY (
            (m_lookup_table.cursorPos () == m_lookup_table.size () - 1) &&
            (fillLookupTableByPage () == FALSE))) {
        return;
    }

    if (G_LIKELY (m_lookup_table.cursorDown ())) {
        updateLookupTableFast ();
    }
}

void
PhoneticEditor::candidateClicked (guint index, guint button, guint state)
{
   selectCandidateInPage (index);
}

void
PhoneticEditor::commit (void)
{
    m_context->commit();
}

void
PhoneticEditor::reset (void)
{
    m_context->reset();
}

void
PhoneticEditor::updateInputText (void)
{
    m_text = m_context->inputText ();
}

void
PhoneticEditor::updateCursor (void)
{
    m_cursor = m_context->cursor ();
}

void
PhoneticEditor::updateAuxiliaryText (void)
{
    String text = m_context->auxiliaryText ();
    updateAuxiliaryTextAfter (text);

    if (text.empty ()) {
        Editor::hideAuxiliaryText ();
    } else {
        StaticText aux_text (text);
        Editor::updateAuxiliaryText (aux_text, TRUE);
    }
}

void
PhoneticEditor::updateAuxiliaryTextAfter (String &buffer)
{
}

void
PhoneticEditor::updateAuxiliaryTextBefore (String &buffer)
{
}

void
PhoneticEditor::updatePreeditText (void)
{
    const String &selected_text = m_context->selectedText ();
    const String &conversion_text = m_context->conversionText ();
    const String &rest_text = m_context->restText ();
    const String whole_text = selected_text + conversion_text + rest_text;
    StaticText preedit_text (whole_text);

    /* underline */
    preedit_text.appendAttribute (
        IBUS_ATTR_TYPE_UNDERLINE, IBUS_ATTR_UNDERLINE_SINGLE, 0, -1);

    /* candidate */
    const guint begin = selected_text.utf8Length ();
    const guint end = begin + conversion_text.utf8Length ();
    if (!conversion_text.empty()) {
        preedit_text.appendAttribute (IBUS_ATTR_TYPE_FOREGROUND, 0x00000000,
                                      begin, end);
        preedit_text.appendAttribute (IBUS_ATTR_TYPE_BACKGROUND, 0x00c8c8f0,
                                      begin, end);
    }

    Editor::updatePreeditText (preedit_text, begin, TRUE);
}

gboolean
PhoneticEditor::selectCandidate (guint i)
{
    if (i >= m_lookup_table.size ())
        return FALSE;
    return m_context->selectCandidate (i);
}

gboolean
PhoneticEditor::selectCandidateInPage (guint i)
{
    guint page_size = m_lookup_table.pageSize ();
    guint cursor_pos = m_lookup_table.cursorPos ();

    if (G_UNLIKELY (i >= page_size))
        return FALSE;
    i += (cursor_pos / page_size) * page_size;

    return selectCandidate (i);
}

gboolean
PhoneticEditor::resetCandidate (guint i)
{
    return m_context->resetCandidate (i);
}

gboolean
PhoneticEditor::resetCandidateInPage (guint i)
{
    guint page_size = m_lookup_table.pageSize ();
    guint cursor_pos = m_lookup_table.cursorPos ();
    i += (cursor_pos / page_size) * page_size;

    return resetCandidate (i);
}

gboolean
PhoneticEditor::unselectCandidates ()
{
    return m_context->unselectCandidates ();
}

void
PhoneticEditor::commitCallback(const String &str)
{
    String commit_text;

    if (G_UNLIKELY (m_props.modeFull ())) {
        for (size_t i = 0; i < str.size (); i++) {
            commit_text.appendUnichar (HalfFullConverter::toFull (str[i]));
        }
    }
    else {
        commit_text = str;
    }

    StaticText text(commit_text);
    commitText (text);
}

};
