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

SUBDIRS = \
	db \
	icons \
	$(NULL)

desktop_in_in_files = \
	ibus-setup-bopomofo.desktop.in.in \
	ibus-setup-pinyin.desktop.in.in \
	$(NULL)

desktop_in_files = $(desktop_in_in_files:.in.in=.in)

$(desktop_in_files): %.desktop.in: %.desktop.in.in Makefile
	$(AM_V_GEN) sed \
		-e "s|\@libexecdir\@|$(libexecdir)|" \
		-e "s|\@pkgdatadir\@|$(pkgdatadir)|" \
		$< > $@.tmp && mv $@.tmp $@

desktop_files = $(desktop_in_files:.desktop.in=.desktop)

desktopdir = $(datadir)/applications
desktop_DATA = $(desktop_files)

EXTRA_DIST = $(desktop_in_in_files)

@INTLTOOL_DESKTOP_RULE@

CLEANFILES = \
	$(desktop_files) \
	$(desktop_in_files) \
	$(NULL)
