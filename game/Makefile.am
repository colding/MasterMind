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

noinst_PROGRAMS = mastermind

mastermind_LDFLAGS = -all-static

mastermind_SOURCES = main.cpp

mastermind_LDADD = \
	$(MASTERMIND_top_dir)/cmdline/libcmdline.la \
	$(MASTERMIND_top_dir)/src/libmastermind.la

AM_CPPFLAGS = $(MASTERMIND_CPPFLAGS)
AM_CXXFLAGS = $(MASTERMIND_CXXFLAGS)

if THIS_IS_NOT_A_DISTRIBUTION
CLEAN_IN_FILES = Makefile.in
else
CLEAN_IN_FILES =
endif

DISTCLEANFILES = $(BUILT_SOURCES) $(CLEAN_IN_FILES) Makefile
CLEANFILES = *~ *.ready
