# $FreeBSD: release/9.0.0/cddl/lib/libzfs/Makefile 219089 2011-02-27 19:41:40Z pjd $

.PATH: ${.CURDIR}/../../../cddl/compat/opensolaris/misc
.PATH: ${.CURDIR}/../../../sys/cddl/contrib/opensolaris/common/zfs
.PATH: ${.CURDIR}/../../../sys/cddl/contrib/opensolaris/uts/common/fs/zfs
.PATH: ${.CURDIR}/../../../cddl/contrib/opensolaris/lib/libzfs/common

LIB=	zfs
DPADD=	${LIBMD} ${LIBPTHREAD} ${LIBUMEM} ${LIBUTIL}
LDADD=	-lmd -lpthread -lumem -lutil

SRCS=	deviceid.c \
	fsshare.c \
	mkdirp.c \
	mnttab.c \
	zmount.c \
	zone.c

SRCS+=	libzfs_changelist.c \
	libzfs_config.c \
	libzfs_dataset.c \
	libzfs_diff.c \
	libzfs_graph.c \
	libzfs_import.c \
	libzfs_mount.c \
	libzfs_pool.c \
	libzfs_sendrecv.c \
	libzfs_status.c \
	libzfs_util.c \
	zfs_comutil.c \
	zfs_deleg.c \
	zfs_fletcher.c \
	zfs_ioctl_compat.c \
	zfs_namecheck.c \
	zfs_prop.c \
	zpool_prop.c \
	zprop_common.c \

WARNS?=	0
CSTD=	c99
CFLAGS+= -DZFS_NO_ACL
CFLAGS+= -I${.CURDIR}/../../../sbin/mount
CFLAGS+= -I${.CURDIR}/../../../cddl/lib/libumem
CFLAGS+= -I${.CURDIR}/../../../sys/cddl/compat/opensolaris
CFLAGS+= -I${.CURDIR}/../../../cddl/compat/opensolaris/include
CFLAGS+= -I${.CURDIR}/../../../cddl/compat/opensolaris/lib/libumem
CFLAGS+= -I${.CURDIR}/../../../cddl/contrib/opensolaris/lib/libzpool/common
CFLAGS+= -I${.CURDIR}/../../../sys/cddl/contrib/opensolaris/common/zfs
CFLAGS+= -I${.CURDIR}/../../../sys/cddl/contrib/opensolaris/uts/common/fs/zfs
CFLAGS+= -I${.CURDIR}/../../../sys/cddl/contrib/opensolaris/uts/common/sys
CFLAGS+= -I${.CURDIR}/../../../cddl/contrib/opensolaris/head
CFLAGS+= -I${.CURDIR}/../../../sys/cddl/contrib/opensolaris/uts/common
CFLAGS+= -I${.CURDIR}/../../../cddl/contrib/opensolaris/lib/libnvpair
CFLAGS+= -I${.CURDIR}/../../../cddl/contrib/opensolaris/lib/libuutil/common
CFLAGS+= -I${.CURDIR}/../../../cddl/contrib/opensolaris/lib/libzfs/common

.include <bsd.lib.mk>
