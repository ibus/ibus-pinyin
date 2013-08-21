# vim:set noet ts=4:
#
# ibus-pinyin - The Chinese PinYin engine for IBus
#
# Copyright (c) 2008-2010 Peng Huang <shawn.p.huang@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.

# @MAINTAINER_MODE_FALSE@skip_gentable=test -f $@ ||

# AM_CFLAGS = \
# 	@IBUS_CFLAGS@ \
# 	@SQLITE_CFLAGS@ \
# 	@PYZY_CFLAGS@ \
# 	-DPKGDATADIR=\"$(pkgdatadir)\" \
# 	$(NULL)
# AM_CXXFLAGS = $(AM_CFLAGS)
# AM_LDADD = \
# 	@IBUS_LIBS@ \
# 	@SQLITE_LIBS@ \
# 	@PYZY_LIBS@ \
# 	$(NULL)
# 

libexec_PROGRAMS = ibus-engine-pinyin
ibus_engine_pinyin_built_c_sources = \
	$(NULL)
ibus_engine_pinyin_built_h_sources = \
	PYPunctTable.h \
	$(NULL)
ibus_engine_pinyin_c_sources = \
	PYBopomofoEditor.cc \
	PYBopomofoEngine.cc \
	PYConfig.cc \
	PYDoublePinyinEditor.cc \
	PYDynamicSpecialPhrase.cc \
	PYEditor.cc \
	PYEngine.cc \
	PYFallbackEditor.cc \
	PYFullPinyinEditor.cc \
	PYHalfFullConverter.cc \
	PYMain.cc \
	PYPhoneticEditor.cc \
	PYPinyinEditor.cc \
	PYPinyinEngine.cc \
	PYPinyinObserver.cc \
	PYPinyinProperties.cc \
	PYPunctEditor.cc \
	$(NULL)
ibus_engine_pinyin_h_sources = \
	PYBopomofoEditor.h \
	PYBopomofoEngine.h \
	PYBus.h \
	PYConfig.h \
	PYDoublePinyinEditor.h \
	PYDynamicSpecialPhrase.h \
	PYEditor.h \
	PYEngine.h \
	PYEnglishEditor.h \
	PYExtEditor.h \
	PYFallbackEditor.h \
	PYFullPinyinEditor.h \
	PYHalfFullConverter.h \
	PYLookupTable.h \
	PYObject.h \
	PYPhoneticEditor.h \
	PYPinyinEditor.h \
	PYPinyinEngine.h \
	PYPinyinObserver.h \
	PYPinyinProperties.h \
	PYPointer.h \
	PYProperty.h \
	PYPunctEditor.h \
	PYRawEditor.h \
	PYRegex.h \
	PYSignal.h \
	PYString.h \
	PYText.h \
	PYTypes.h \
	PYUtil.h \
	$(NULL)

if IBUS_BUILD_LUA_EXTENSION
ibus_engine_pinyin_c_sources += PYExtEditor.cc
endif

if IBUS_BUILD_ENGLISH_INPUT_MODE
ibus_engine_pinyin_c_sources += PYEnglishEditor.cc
endif

ibus_engine_pinyin_SOURCES = \
	$(ibus_engine_pinyin_c_sources) \
	$(ibus_engine_pinyin_h_sources) \
	$(ibus_engine_pinyin_built_c_sources) \
	$(ibus_engine_pinyin_built_h_sources) \
	$(NULL)


ibus_engine_pinyin_CXXFLAGS = \
	@IBUS_CFLAGS@ \
	@SQLITE_CFLAGS@ \
	@PYZY_CFLAGS@ \
	-DGETTEXT_PACKAGE=\"@GETTEXT_PACKAGE@\" \
	-DPKGDATADIR=\"$(pkgdatadir)\" \
	-DLIBEXECDIR=\"$(libexecdir)\" \
	$(NULL)

if HAVE_BOOST
ibus_engine_pinyin_CXXFLAGS += \
	@BOOST_CPPFLAGS@ \
	$(NULL)
else
ibus_engine_pinyin_CXXFLAGS += \
	-std=c++0x \
	$(NULL)
endif

ibus_engine_pinyin_LDADD = \
	@IBUS_LIBS@ \
	@SQLITE_LIBS@ \
	@PYZY_LIBS@ \
	$(NULL)

if IBUS_BUILD_LUA_EXTENSION
    ibus_engine_pinyin_CXXFLAGS +=  \
	@LUA_CFLAGS@ \
	-DIBUS_BUILD_LUA_EXTENSION \
	-I$(top_srcdir)/lua/ \
	$(NULL)
endif

if IBUS_BUILD_LUA_EXTENSION
    ibus_engine_pinyin_LDADD += \
	@LUA_LIBS@ \
	-L../lua/ \
	-lpylua \
	$(NULL)
endif

if IBUS_BUILD_ENGLISH_INPUT_MODE
   ibus_engine_pinyin_CXXFLAGS += \
	-DIBUS_BUILD_ENGLISH_INPUT_MODE \
	$(NULL)
endif

BUILT_SOURCES = \
	$(ibus_engine_built_c_sources) \
	$(ibus_engine_built_h_sources) \
	$(NULL)

pkgdata_DATA = \
	phrases.txt \
	$(NULL)

component_DATA = \
	pinyin.xml \
	$(NULL)
componentdir = @datadir@/ibus/component

EXTRA_DIST = \
	pinyin.xml.in \
	phrases.txt \
	$(NULL)

CLEANFILES = \
	pinyin.xml \
	$(NULL)

PYPunctTable.h:
	$(AM_V_GEN) \
	$(PYTHON) $(top_srcdir)/scripts/genpuncttable.py > $@ || \
		( $(RM) $@; exit 1 )

pinyin.xml: pinyin.xml.in
	$(AM_V_GEN) \
	( \
		libexecdir=${libexecdir}; \
		pkgdatadir=${pkgdatadir}; \
		s=`cat $<`; \
		eval "echo \"$${s}\""; \
	) > $@

test: ibus-engine-pinyin
	$(ENV_IBUS_TEST) \
		G_DEBUG=fatal_criticals \
		$(builddir)/ibus-engine-pinyin

# test: ibus-engine-pinyin
# 	$(ENV_IBUS_TEST) G_DEBUG=fatal_warnings \
# 	$(builddir)/ibus-engine-pinyin
