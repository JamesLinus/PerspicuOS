#	@(#)Makefile	5.2 (Berkeley) 12/28/90
#	$Id: Makefile,v 1.6 1994/06/30 05:33:39 cgd Exp $
# $FreeBSD: release/9.0.0/usr.bin/make/Makefile 201386 2010-01-02 10:27:05Z ed $

PROG=	make
CFLAGS+=-I${.CURDIR}
SRCS=	arch.c buf.c cond.c dir.c for.c hash.c hash_tables.c job.c	\
	lst.c main.c make.c parse.c proc.c shell.c str.c suff.c targ.c	\
	util.c var.c

NO_SHARED?=	YES

CFLAGS+=-DMAKE_VERSION=\"5200408120\"
# There is no obvious performance improvement currently.
# CFLAGS+=-DUSE_KQUEUE

# Make object files which depend on preprocessor symbols defined in
# the Makefile which are not compilation options but rather configuration
# options dependend on the Makefile. main.c needs MAKE_VERSION while
# shell.c uses DEFSHELLNAME. This will cause recompilation in the case
# the definition is changed in the makefile. It will of course not cause
# recompilation if one does 'make MAKE_SHELL=csh'.
main.o shell.o: ${MAKEFILE}

# Directive and keyword tables. We use hash tables. These hash tables have been
# generated with mph (ports/devel/mph)
# If you change the directives or keywords (adding, deleting, reordering) you
# need to create new tables and hash functions (directive_hash, keyword_hash).
#
# The following changes have been made to the generated code:
#
#	o prefix the names of the g, T0 and T1 arrays with 'directive_'
#	  resp. 'keyword_'.
#
#	o make the type of the tables 'const [un]signed char' (if you change
#	  anything make sure that the numbers fit into a char).
#
#	o make the hash function use the length for termination,
#	  not the trailing '\0', via the -l flag in emitc and some editing
#	  (only for directive_hash).

LOCALBASE ?= /usr/local
MPH	?= ${LOCALBASE}/bin/mph
EMITC	?= ${LOCALBASE}/bin/emitc

.PRECIOUS: hash

hash:
	( echo '/*' ;							\
	  echo ' * DO NOT EDIT' ;					\
	  echo ' * $$''FreeBSD$$' ;					\
	  echo -n ' * auto-generated from ' ;				\
	  sed -nEe '/\$$FreeBSD/s/^.*\$$(.*)\$$.*$$/\1/p'		\
		${.CURDIR}/parse.c ;					\
	  echo ' * DO NOT EDIT' ;					\
	  echo ' */' ;							\
	  echo '#include <sys/types.h>' ;				\
	  echo ;							\
	  echo '#include "hash_tables.h"' ;				\
	  echo ;							\
	  cat ${.CURDIR}/parse.c | sed					\
	    -e '1,/DIRECTIVES-START-TAG/d'				\
	    -e '/DIRECTIVES-END-TAG/,$$d'				\
	    -e 's/^[^"]*"\([^"]*\)".*$$/\1/' |				\
	    ${MPH} -d2 -m1 | ${EMITC} -l -s |				\
	    sed								\
	    -e 's/^static int g\[\]/static const signed char directive_g[]/' \
	    -e 's/^static int T0\[\]/static const u_char directive_T0[]/' \
	    -e 's/^static int T1\[\]/static const u_char directive_T1[]/' \
	    -e '/^#define uchar unsigned char/d'			\
	    -e 's/uchar/u_char/g'					\
	    -e 's/^hash(/directive_hash(/'				\
	    -e 's/; \*kp;/; kp < key + len;/'				\
	    -e 's/int len)/size_t len)/'				\
	    -e 's/= T0\[/= directive_T0\[/'				\
	    -e 's/= T1\[/= directive_T1\[/'				\
	    -e 's/g\[f/directive_g[f/g' ;				\
	  cat ${.CURDIR}/parse.c | sed					\
	    -e '1,/KEYWORD-START-TAG/d'					\
	    -e '/KEYWORD-END-TAG/,$$d'					\
	    -e 's/^[^"]*"\([^"]*\)".*$$/\1/' |				\
	    ${MPH} -d2 -m1 | ${EMITC} -l -s |				\
	    sed								\
	    -e 's/^static int g\[\]/static const signed char keyword_g[]/' \
	    -e 's/^static int T0\[\]/static const u_char keyword_T0[]/' \
	    -e 's/^static int T1\[\]/static const u_char keyword_T1[]/' \
	    -e '/^#define uchar unsigned char/d'			\
	    -e 's/uchar/u_char/g'					\
	    -e 's/^hash(/keyword_hash(/'				\
	    -e 's/int len)/size_t len)/'				\
	    -e 's/= T0\[/= keyword_T0\[/'				\
	    -e 's/= T1\[/= keyword_T1\[/'				\
	    -e 's/g\[f/keyword_g[f/g'					\
	) > ${.CURDIR}/hash_tables.c

# Set the shell which make(1) uses.  Bourne is the default, but a decent
# Korn shell works fine, and much faster.  Using the C shell for this
# will almost certainly break everything, but it's Unix tradition to
# allow you to shoot yourself in the foot if you want to :-)

MAKE_SHELL?=	sh
.if ${MAKE_SHELL} == "csh" || ${MAKE_SHELL} == "sh" || ${MAKE_SHELL} == "ksh"
CFLAGS+=	-DDEFSHELLNAME=\"${MAKE_SHELL}\"
.else
.error "MAKE_SHELL must be set to one of \"csh\", \"sh\" or \"ksh\"."
.endif

.include <bsd.prog.mk>
