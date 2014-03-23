#  
# Copyright (C) 2014 Jules Colding <jcolding@gmail.com>.
#
# All Rights Reserved.
#
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.  This file is offered as-is,
# without any warranty.
#

SUBDIRS = 

noinst_LTLIBRARIES = libmastermind.la
libmastermind_la_LDFLAGS = -static

libmastermind_la_SOURCES = \
	mastermind.cpp     \
	mastermind.h       \
	gameboard.cpp      \
	gameboard.h        \
	code_breaker.cpp   \
	code_breaker.h     \
	code_maker.cpp     \
	code_maker.h

AM_CPPFLAGS = $(MASTERMIND_CPPFLAGS)
AM_CXXFLAGS = $(MASTERMIND_CXXFLAGS)

if THIS_IS_NOT_A_DISTRIBUTION
CLEAN_IN_FILES = Makefile.in
else
CLEAN_IN_FILES =
endif

DISTCLEANFILES = $(BUILT_SOURCES) $(CLEAN_IN_FILES) Makefile
CLEANFILES = *~
