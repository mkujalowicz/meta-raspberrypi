FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += "file://qmake.patch"

EXTRA_OECONF := "${@oe_filter_out('-qpa wayland-egl', '${EXTRA_OECONF}', d)}"
EXTRA_OECONF += "-qpa wayland-brcm"
