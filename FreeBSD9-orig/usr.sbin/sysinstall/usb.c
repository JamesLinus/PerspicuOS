/*
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
 * used floppy.c and cdrom.c as templates, edited as necessary.
 *
 * $FreeBSD: release/9.0.0/usr.sbin/sysinstall/usb.c 194931 2009-06-24 23:17:00Z cperciva $
 */

#include <sys/fcntl.h>
#include <sys/param.h>
#include <sys/mount.h>

#include <ufs/ufs/ufsmount.h>

#include "sysinstall.h"

static Boolean USBMounted;
static char mountpoint[] = "/dist";

Boolean
mediaInitUSB(Device *dev)
{
	struct ufs_args ufsargs;

	if (USBMounted)
		return TRUE;

	Mkdir(mountpoint);

	memset(&ufsargs, 0, sizeof(ufsargs));
	ufsargs.fspec = dev->devname;

	if (mount("ufs", mountpoint, MNT_RDONLY, (caddr_t)&ufsargs) != -1) {
		USBMounted = TRUE;
		return TRUE;
	}

	msgConfirm("Error mounting USB drive %s (%s) on %s : %s",
	    dev->name, dev->devname, mountpoint, strerror(errno));
	return FALSE;
}


FILE *
mediaGetUSB(Device *dev, char *file, Boolean probe)
{
	return mediaGenericGet(mountpoint, file);
}


/* 
 * When sysinstall terminates, all USB drives handled by deviceRegister will 
 * be checked and unmounted if necessary.
 */
void
mediaShutdownUSB(Device *dev)
{
	if (!USBMounted) 
		return;

	if (unmount(mountpoint, MNT_FORCE) != 0)
		msgConfirm("Could not unmount the USB drive from %s: %s", 
				mountpoint, strerror(errno));
	else
		USBMounted = FALSE;

}
