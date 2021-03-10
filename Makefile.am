lib_LTLIBRARIES = countdownAutokill.la

countdownAutokill_la_SOURCES = countdownAutokill.cpp
countdownAutokill_la_CPPFLAGS= -I$(top_srcdir)/include -I$(top_srcdir)/plugins/plugin_utils
countdownAutokill_la_LDFLAGS = -module -avoid-version -shared
countdownAutokill_la_LIBADD = $(top_builddir)/plugins/plugin_utils/libplugin_utils.la

AM_CPPFLAGS = $(CONF_CPPFLAGS)
AM_CFLAGS = $(CONF_CFLAGS)
AM_CXXFLAGS = $(CONF_CXXFLAGS)

EXTRA_DIST = \
	README.md \
	countdownAutokill.sln \
	countdownAutokill.vcxproj	\
	countdownAutokill.vcxproj.filters

MAINTAINERCLEANFILES =	\
	Makefile.in
