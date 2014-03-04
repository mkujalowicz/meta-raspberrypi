FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += "file://raspberrypi.patch \
            file://battery.patch"
