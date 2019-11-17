SUBDIRS = ../lib/tr_util_date_time

AM_CPPFLAGS = -I$(srcdir)/../lib/tr_util_date_time/src

bin_PROGRAMS = sample

sample_SOURCES = sample.cc
sample_LDFLAGS = -L../lib/tr_util_date_time/src
sample_LDADD = -ltr_util_date_time
