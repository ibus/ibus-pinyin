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
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#ifndef __PY_BOPOMOFO_KEYBOARD_H_
#define __PY_BOPOMOFO_KEYBOARD_H_

#include "PYBopomofo.h"

static const guint8
bopomofo_keyboard[][42][2] = {
    {
        { ' ' , BOPOMOFO_TONE_1 },
        { ',' , BOPOMOFO_E2     },
        { '-' , BOPOMOFO_ER     },
        { '.' , BOPOMOFO_OU     },
        { '/' , BOPOMOFO_ENG    },
        { '0' , BOPOMOFO_AN     },
        { '1' , BOPOMOFO_B      },
        { '2' , BOPOMOFO_D      },
        { '3' , BOPOMOFO_TONE_3 },
        { '4' , BOPOMOFO_TONE_4 },
        { '5' , BOPOMOFO_ZH     },
        { '6' , BOPOMOFO_TONE_2 },
        { '7' , BOPOMOFO_TONE_5 },
        { '8' , BOPOMOFO_A      },
        { '9' , BOPOMOFO_AI     },
        { ';' , BOPOMOFO_ANG    },
        { 'a' , BOPOMOFO_M      },
        { 'b' , BOPOMOFO_R      },
        { 'c' , BOPOMOFO_H      },
        { 'd' , BOPOMOFO_K      },
        { 'e' , BOPOMOFO_G      },
        { 'f' , BOPOMOFO_Q      },
        { 'g' , BOPOMOFO_SH     },
        { 'h' , BOPOMOFO_C      },
        { 'i' , BOPOMOFO_O      },
        { 'j' , BOPOMOFO_U      },
        { 'k' , BOPOMOFO_E      },
        { 'l' , BOPOMOFO_AO     },
        { 'm' , BOPOMOFO_V      },
        { 'n' , BOPOMOFO_S      },
        { 'o' , BOPOMOFO_EI     },
        { 'p' , BOPOMOFO_EN     },
        { 'q' , BOPOMOFO_P      },
        { 'r' , BOPOMOFO_J      },
        { 's' , BOPOMOFO_N      },
        { 't' , BOPOMOFO_CH     },
        { 'u' , BOPOMOFO_I      },
        { 'v' , BOPOMOFO_X      },
        { 'w' , BOPOMOFO_T      },
        { 'x' , BOPOMOFO_L      },
        { 'y' , BOPOMOFO_Z      },
        { 'z' , BOPOMOFO_F      },
    },
    {
        { ' ' , BOPOMOFO_TONE_1 },
        { '\'', BOPOMOFO_V      },
        { ',' , BOPOMOFO_E2     },
        { '-' , BOPOMOFO_I      },
        { '.' , BOPOMOFO_OU     },
        { '/' , BOPOMOFO_ENG    },
        { '0' , BOPOMOFO_AN     },
        { '1' , BOPOMOFO_TONE_5 },
        { '2' , BOPOMOFO_B      },
        { '3' , BOPOMOFO_D      },
        { '6' , BOPOMOFO_ZH     },
        { '8' , BOPOMOFO_A      },
        { '9' , BOPOMOFO_AI     },
        { ';' , BOPOMOFO_ANG    },
        { '=' , BOPOMOFO_ER     },
        { '[' , BOPOMOFO_U      },
        { 'a' , BOPOMOFO_TONE_3 },
        { 'b' , BOPOMOFO_X      },
        { 'c' , BOPOMOFO_L      },
        { 'd' , BOPOMOFO_N      },
        { 'e' , BOPOMOFO_T      },
        { 'f' , BOPOMOFO_K      },
        { 'g' , BOPOMOFO_Q      },
        { 'h' , BOPOMOFO_SH     },
        { 'i' , BOPOMOFO_O      },
        { 'j' , BOPOMOFO_C      },
        { 'k' , BOPOMOFO_E      },
        { 'l' , BOPOMOFO_AO     },
        { 'm' , BOPOMOFO_S      },
        { 'n' , BOPOMOFO_R      },
        { 'o' , BOPOMOFO_EI     },
        { 'p' , BOPOMOFO_EN     },
        { 'q' , BOPOMOFO_TONE_2 },
        { 'r' , BOPOMOFO_G      },
        { 's' , BOPOMOFO_M      },
        { 't' , BOPOMOFO_J      },
        { 'u' , BOPOMOFO_Z      },
        { 'v' , BOPOMOFO_H      },
        { 'w' , BOPOMOFO_P      },
        { 'x' , BOPOMOFO_F      },
        { 'y' , BOPOMOFO_CH     },
        { 'z' , BOPOMOFO_TONE_4 },
    },
    {
        { ' ' , BOPOMOFO_TONE_1 },
        { '\'', BOPOMOFO_C      },
        { ',' , BOPOMOFO_ZH     },
        { '-' , BOPOMOFO_ENG    },
        { '.' , BOPOMOFO_CH     },
        { '/' , BOPOMOFO_SH     },
        { '0' , BOPOMOFO_ANG    },
        { '1' , BOPOMOFO_TONE_5 },
        { '2' , BOPOMOFO_TONE_2 },
        { '3' , BOPOMOFO_TONE_3 },
        { '4' , BOPOMOFO_TONE_4 },
        { '7' , BOPOMOFO_Q      },
        { '8' , BOPOMOFO_AN     },
        { '9' , BOPOMOFO_EN     },
        { ';' , BOPOMOFO_Z      },
        { '=' , BOPOMOFO_ER     },
        { 'a' , BOPOMOFO_A      },
        { 'b' , BOPOMOFO_B      },
        { 'c' , BOPOMOFO_X      },
        { 'd' , BOPOMOFO_D      },
        { 'e' , BOPOMOFO_I      },
        { 'f' , BOPOMOFO_F      },
        { 'g' , BOPOMOFO_J      },
        { 'h' , BOPOMOFO_H      },
        { 'i' , BOPOMOFO_AI     },
        { 'j' , BOPOMOFO_R      },
        { 'k' , BOPOMOFO_K      },
        { 'l' , BOPOMOFO_L      },
        { 'm' , BOPOMOFO_M      },
        { 'n' , BOPOMOFO_N      },
        { 'o' , BOPOMOFO_O      },
        { 'p' , BOPOMOFO_P      },
        { 'q' , BOPOMOFO_EI     },
        { 'r' , BOPOMOFO_E      },
        { 's' , BOPOMOFO_S      },
        { 't' , BOPOMOFO_T      },
        { 'u' , BOPOMOFO_V      },
        { 'v' , BOPOMOFO_G      },
        { 'w' , BOPOMOFO_E2     },
        { 'x' , BOPOMOFO_U      },
        { 'y' , BOPOMOFO_OU     },
        { 'z' , BOPOMOFO_AO     },
    },
    {
        { ' ' , BOPOMOFO_TONE_1 },
        { ',' , BOPOMOFO_TONE_3 },
        { '-' , BOPOMOFO_H      },
        { '.' , BOPOMOFO_TONE_4 },
        { '/' , BOPOMOFO_TONE_5 },
        { '0' , BOPOMOFO_K      },
        { '1' , BOPOMOFO_B      },
        { '2' , BOPOMOFO_P      },
        { '3' , BOPOMOFO_M      },
        { '4' , BOPOMOFO_F      },
        { '5' , BOPOMOFO_D      },
        { '6' , BOPOMOFO_T      },
        { '7' , BOPOMOFO_N      },
        { '8' , BOPOMOFO_L      },
        { '9' , BOPOMOFO_G      },
        { ';' , BOPOMOFO_AO     },
        { 'a' , BOPOMOFO_I      },
        { 'b' , BOPOMOFO_ENG    },
        { 'c' , BOPOMOFO_EN     },
        { 'd' , BOPOMOFO_V      },
        { 'e' , BOPOMOFO_X      },
        { 'f' , BOPOMOFO_A      },
        { 'g' , BOPOMOFO_O      },
        { 'h' , BOPOMOFO_E      },
        { 'i' , BOPOMOFO_Z      },
        { 'j' , BOPOMOFO_E2     },
        { 'k' , BOPOMOFO_AI     },
        { 'l' , BOPOMOFO_EI     },
        { 'm' , BOPOMOFO_TONE_2 },
        { 'n' , BOPOMOFO_ER     },
        { 'o' , BOPOMOFO_C      },
        { 'p' , BOPOMOFO_S      },
        { 'q' , BOPOMOFO_J      },
        { 'r' , BOPOMOFO_ZH     },
        { 's' , BOPOMOFO_U      },
        { 't' , BOPOMOFO_CH     },
        { 'u' , BOPOMOFO_R      },
        { 'v' , BOPOMOFO_ANG    },
        { 'w' , BOPOMOFO_Q      },
        { 'x' , BOPOMOFO_AN     },
        { 'y' , BOPOMOFO_SH     },
        { 'z' , BOPOMOFO_OU     },
    },
};

#endif /* __PY_BOPOMOFO_KEYBOARD_H_ */
