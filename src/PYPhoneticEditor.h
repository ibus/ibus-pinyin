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
#ifndef __PY_PHONETIC_EDITOR_H_
#define __PY_PHONETIC_EDITOR_H_

#include <PyZy/InputContext.h>

#include "PYEditor.h"
#include "PYLookupTable.h"
#include "PYPinyinObserver.h"
#include "PYUtil.h"

namespace PY {

class PhoneticEditor : public Editor {
public:
    PhoneticEditor (PinyinProperties & props, Config & config);
    virtual ~PhoneticEditor ();

public:
    /* virtual functions */
    virtual gboolean insert (gint ch);

    virtual gboolean removeCharBefore (void);
    virtual gboolean removeCharAfter (void);
    virtual gboolean removeWordBefore (void);
    virtual gboolean removeWordAfter (void);

    virtual gboolean moveCursorLeft (void);
    virtual gboolean moveCursorRight (void);
    virtual gboolean moveCursorLeftByWord (void);
    virtual gboolean moveCursorRightByWord (void);
    virtual gboolean moveCursorToBegin (void);
    virtual gboolean moveCursorToEnd (void);

    virtual void pageUp (void);
    virtual void pageDown (void);
    virtual void cursorUp (void);
    virtual void cursorDown (void);
    virtual void commit (void);
    virtual void reset (void);

    virtual void candidateClicked (guint index, guint button, guint state);
    virtual gboolean processKeyEvent (guint keyval, guint keycode, guint modifiers);
    virtual gboolean processSpace (guint keyval, guint keycode, guint modifiers);
    virtual gboolean processFunctionKey (guint keyval, guint keycode, guint modifiers);
    virtual void updateInputText (void);
    virtual void updateCursor (void);
    virtual void updateAuxiliaryText (void);
    virtual void updateAuxiliaryTextBefore (String &buffer);
    virtual void updateAuxiliaryTextAfter (String &buffer);
    virtual void updatePreeditText (void);
    virtual void updateLookupTable (void);
    virtual void updateLookupTableFast (void);
    virtual gboolean fillLookupTableByPage (void);

    void commitCallback (const String & commit_text);

protected:
    void setContext (PyZy::InputContext::InputType type);
    void unsetContext ();

    gboolean selectCandidate (guint i);
    gboolean selectCandidateInPage (guint i);
    gboolean resetCandidate (guint i);
    gboolean resetCandidateInPage (guint i);
    gboolean unselectCandidates (void);

    /* varibles */
    std::unique_ptr<PyZy::InputContext>  m_context;
    PinyinObserver                       m_observer;
    LookupTable                          m_lookup_table;
};
};

#endif
