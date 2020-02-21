##############################################################################
##                                 qlibclib                                 ##
##                                                                          ##
##                   Copyright © 2010-2015 Seungyoung Kim                   ##
##                      Copyright © 2019 ARQADIUM, LLC                      ##
##                           All rights reserved.                           ##
##############################################################################

include base.mk

# name of project. used in output binary naming
PROJECT := qlibc

# put a ‘1’ for the desired target types to compile
EXEFILE :=
SOFILE  :=
AFILE   := 1

# space-separated path list for #includes
# <system> includes
INCLUDES := include
# "local" includes
INCLUDEL := src include/qlibc src/internal

# space-separated library name list for linking
# libraries
LIBS      := pthread
LIBDIRS   :=

# ‘3P’ are 3rd-party dependencies
# 3PLIBDIR is the base directory
# 3PLIBS is the folder names in the base directory for each library
3PLIBDIR := 3rdparty
3PLIBS   :=

# frameworks (macOS only)
FWORKS :=

CFILES    := \
	src/containers/qgrow.c \
	src/containers/qhasharr.c \
	src/containers/qhashtbl.c \
	src/containers/qlist.c \
	src/containers/qlisttbl.c \
	src/containers/qqueue.c \
	src/containers/qstack.c \
	src/containers/qtreetbl.c \
	src/containers/qvector.c \
	src/extensions/qaconf.c \
	src/extensions/qconfig.c \
	src/extensions/qdatabase.c \
	src/extensions/qhttpclient.c \
	src/extensions/qlog.c \
	src/extensions/qtokenbucket.c \
	src/internal/md5/md5c.c \
	src/internal/qinternal.c \
	src/ipc/qsem.c \
	src/ipc/qshm.c \
	src/utilities/qcount.c \
	src/utilities/qencode.c \
	src/utilities/qfile.c \
	src/utilities/qhash.c \
	src/utilities/qio.c \
	src/utilities/qsocket.c \
	src/utilities/qstring.c \
	src/utilities/qsystem.c \
	src/utilities/qtime.c
HFILES    := \
	include/qlibc/containers/qgrow.h \
	include/qlibc/containers/qhasharr.h \
	include/qlibc/containers/qhashtbl.h \
	include/qlibc/containers/qlist.h \
	include/qlibc/containers/qlisttbl.h \
	include/qlibc/containers/qqueue.h \
	include/qlibc/containers/qstack.h \
	include/qlibc/containers/qtreetbl.h \
	include/qlibc/containers/qvector.h \
	include/qlibc/extensions/qaconf.h \
	include/qlibc/extensions/qconfig.h \
	include/qlibc/extensions/qdatabase.h \
	include/qlibc/extensions/qhttpclient.h \
	include/qlibc/extensions/qlog.h \
	include/qlibc/extensions/qtokenbucket.h \
	include/qlibc/ipc/qsem.h \
	include/qlibc/ipc/qshm.h \
	include/qlibc/utilities/qcount.h \
	include/qlibc/utilities/qencode.h \
	include/qlibc/utilities/qfile.h \
	include/qlibc/utilities/qhash.h \
	include/qlibc/utilities/qio.h \
	include/qlibc/utilities/qsocket.h \
	include/qlibc/utilities/qstring.h \
	include/qlibc/utilities/qsystem.h \
	include/qlibc/utilities/qtime.h \
	include/qlibc/qlibc.h \
	include/qlibc/qlibcext.h
CPPFILES  :=
HPPFILES  :=
OFILES    := $(CFILES:.c=.c.o) $(CPPFILES:.cpp=.cpp.o)
# address-sanitisation metadata
GCNOFILES := $(CFILES:.c=.c.gcno) $(CPPFILES:.cpp=.cpp.gcno)
GCDAFILES := $(CFILES:.c=.c.gcda) $(CPPFILES:.cpp=.cpp.gcda)

NO_TES := 1
CFLAGS += -std=c99

.PHONY: default

default: debug

# this defines all our usual targets
include targets.mk
