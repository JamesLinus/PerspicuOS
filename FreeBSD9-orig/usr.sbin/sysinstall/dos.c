/*
 * The new sysinstall program.
 *
 * This is probably the last attempt in the `sysinstall' line, the next
 * generation being slated to essentially a complete rewrite.
 *
 * $FreeBSD: release/9.0.0/usr.sbin/sysinstall/dos.c 77580 2001-06-01 12:16:09Z ru $
 *
 * Copyright (c) 1995
 *	Jordan Hubbard.  All rights reserved.
 * Copyright (c) 1995
 * 	Gary J Palmer. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer,
 *    verbatim and that no modifications are made prior to this
 *    point in the file.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY JORDAN HUBBARD ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL JORDAN HUBBARD OR HIS PETS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, LIFE OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#include "sysinstall.h"
#include <sys/stat.h>
#include <sys/errno.h>
#include <sys/param.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <grp.h>
#define MSDOSFS
#include <sys/mount.h>
#include <fs/msdosfs/msdosfsmount.h>
#undef MSDOSFS

static Boolean DOSMounted;
static char mountpoint[] = "/dist";

Boolean
mediaInitDOS(Device *dev)
{
    struct msdosfs_args args;

    if (DOSMounted)
	return TRUE;
     
    Mkdir(mountpoint);
    memset(&args, 0, sizeof(args));
    args.fspec = dev->devname;
    args.uid = args.gid = 0;
    args.mask = 0777;

    if (mount("msdosfs", mountpoint, MNT_RDONLY, (caddr_t)&args) == -1) {
	msgConfirm("Error mounting %s on %s: %s (%u)", args.fspec, mountpoint, strerror(errno), errno);
	return FALSE;
    }
    DOSMounted = TRUE;
    return TRUE;
}

FILE *
mediaGetDOS(Device *dev, char *file, Boolean probe)
{
    return mediaGenericGet(mountpoint, file);
}

void
mediaShutdownDOS(Device *dev)
{
    if (!DOSMounted)
	return;
    if (unmount(mountpoint, MNT_FORCE) != 0)
	msgConfirm("Could not unmount the DOS partition from %s: %s",
		   mountpoint, strerror(errno));
    else
	DOSMounted = FALSE;
    return;
}
