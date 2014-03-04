DESCRIPTION = "Graphics libraries for BCM2835."
LICENSE = "Proprietary"

LIC_FILES_CHKSUM = "file://LICENCE;md5=86e53f5f5909ee66900418028de11780"

PROVIDES = "virtual/libgles2 virtual/egl"
COMPATIBLE_MACHINE = "raspberrypi"

include ../common/firmware.inc

SRC_URI = "git://github.com/raspberrypi/firmware.git;protocol=git;branch=master\
           file://egl.pc \
           file://glesv2.pc \
           file://glesv1_cm.pc \
           file://vchiq.sh"

S = "${WORKDIR}/git/${VCDIR}"

INCPR = "r1"

inherit pkgconfig update-rc.d

do_install () {
  install -d ${D}/opt/vc/bin
  cp -R bin/* ${D}/opt/vc/bin

  install -d ${D}/opt/vc/sbin
  cp -R sbin/* ${D}/opt/vc/sbin

  install -d ${D}/opt/vc/lib
  # note: -H option to deref symlinked .so
  cp -R -H lib/*.so ${D}/opt/vc/lib

  install -d ${D}/opt/vc/include
  cp -R include/* ${D}/opt/vc/include

  install -d ${D}${libdir}/pkgconfig
  install -m 0644 ${WORKDIR}/egl.pc ${D}${libdir}/pkgconfig/
  install -m 0644 ${WORKDIR}/glesv2.pc ${D}${libdir}/pkgconfig/
  install -m 0644 ${WORKDIR}/glesv1_cm.pc ${D}${libdir}/pkgconfig/

  install -d ${D}/${sysconfdir}/init.d
  install -m 0755 ${WORKDIR}/vchiq.sh ${D}${sysconfdir}/init.d/
}

sysroot_stage_all_append() {
        sysroot_stage_dir ${D}/opt/vc ${SYSROOT_DESTDIR}/opt/vc
}


# These are proprietary binaries generated elsewhere so don't check ldflags
INSANE_SKIP_${PN} = "ldflags"

INITSCRIPT_NAME = "vchiq.sh"
INITSCRIPT_PARAMS = "start 03 S ."

FILES_${PN} = "/opt/vc/bin \
               /opt/vc/sbin \
               /opt/vc/lib/*.so \
               ${sysconfdir}/init.d"

FILES_${PN}-dbg += "/opt/vc/bin/.debug \
                   /opt/vc/sbin/.debug"

FILES_${PN}-dev = "${libdir}/pkgconfig \
                   /opt/vc/include"
