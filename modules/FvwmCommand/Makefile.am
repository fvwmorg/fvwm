## Process this file with automake to create Makefile.in

PERL = @PERL@

SUBDIRS = scripts

bin_PROGRAMS = FvwmCommand
moduledir = @FVWM_MODULEDIR@

FvwmCommand_SOURCES = FvwmCommand.c FvwmCommand.h fifos.c

FvwmCommand_DEPENDENCIES = $(top_builddir)/libs/libfvwm.a

man_MANS = FvwmCommand.1

EXTRA_DIST = $(man_MANS)

LDADD = -L$(top_builddir)/libs -lfvwm

# FIXME:
# Despite not using X functions explicitly, the code includes
# fvwmlib.h, which *does* include X headers and xpm.h!
AM_CPPFLAGS = -I$(top_srcdir) $(xpm_CFLAGS) $(Xft_CFLAGS) $(X_CFLAGS)
