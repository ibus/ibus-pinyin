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
#ifndef __PY_PINYIN_OBSERVER_H_
#define __PY_PINYIN_OBSERVER_H_

#include <PyZy/InputContext.h>

namespace PY {

class PhoneticEditor;

class PinyinObserver : public PyZy::InputContext::Observer {
public:
    explicit PinyinObserver (PhoneticEditor &editor);

    virtual void commitText (const PyZy::InputContext * context,
                             const std::string &commit_text);
    virtual void inputTextChanged (const PyZy::InputContext * context);
    virtual void cursorChanged (const PyZy::InputContext * context);
    virtual void preeditTextChanged (const PyZy::InputContext * context);
    virtual void auxiliaryTextChanged (const PyZy::InputContext * context);
    virtual void candidatesChanged (const PyZy::InputContext * context);

private:
    PhoneticEditor &m_editor;
};

}  // namespace PY

#endif
