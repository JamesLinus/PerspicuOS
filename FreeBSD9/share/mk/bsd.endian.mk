# $FreeBSD: release/9.0.0/share/mk/bsd.endian.mk 217123 2011-01-07 20:26:33Z imp $

.if ${MACHINE_ARCH} == "amd64" || \
    ${MACHINE_ARCH} == "i386" || \
    ${MACHINE_ARCH} == "ia64" || \
    ${MACHINE_ARCH} == "arm"  || \
    ${MACHINE_ARCH:Mmips*el} != ""
TARGET_ENDIANNESS= 1234
.elif ${MACHINE_ARCH} == "powerpc" || \
    ${MACHINE_ARCH} == "powerpc64" || \
    ${MACHINE_ARCH} == "sparc64" || \
    ${MACHINE_ARCH} == "armeb" || \
    ${MACHINE_ARCH:Mmips*eb} != ""
TARGET_ENDIANNESS= 4321
.endif
