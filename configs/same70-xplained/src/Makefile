############################################################################
# configs/same70-xplained/src/Makefile
#
#   Copyright (C) 2015, 2017 Gregory Nutt. All rights reserved.
#   Author: Gregory Nutt <gnutt@nuttx.org>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
# 3. Neither the name NuttX nor the names of its contributors may be
#    used to endorse or promote products derived from this software
#    without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
# OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
# AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
############################################################################

-include $(TOPDIR)/Make.defs

ASRCS =
CSRCS = sam_boot.c

ifeq ($(CONFIG_SAMV7_SDRAMC),y)
CSRCS += sam_sdram.c
endif

ifeq ($(CONFIG_LIB_BOARDCTL),y)
CSRCS += sam_appinit.c sam_bringup.c
else ifeq ($(CONFIG_BOARD_INITIALIZE),y)
CSRCS += sam_bringup.c
endif

ifeq ($(CONFIG_ARCH_LEDS),y)
CSRCS += sam_autoleds.c
else
CSRCS += sam_userleds.c
endif

ifeq ($(CONFIG_ARCH_BUTTONS),y)
CSRCS += sam_buttons.c
endif

ifeq ($(CONFIG_SAMV7_HSMCI0),y)
CSRCS += sam_hsmci.c
endif

ifeq ($(CONFIG_SAMV7_EMAC),y)
CSRCS += sam_ethernet.c
endif

ifeq ($(CONFIG_SAMV7_USBDEVHS),y)
CSRCS += sam_usbdev.c
endif

ifeq ($(CONFIG_SAMV7_SPI),y)
CSRCS += sam_spi.c
endif

ifeq ($(CONFIG_USBMSC),y)
CSRCS += sam_usbmsc.c
endif

ifeq ($(CONFIG_SAMV7_MCAN),y)
CSRCS += sam_mcan.c
endif

ifeq ($(CONFIG_MTD_CONFIG),y)
ifeq ($(CONFIG_SAMV7_TWIHS0),y)
ifeq ($(CONFIG_MTD_AT24XX),y)
CSRCS += sam_at24config.c
endif
endif
endif

ifneq (,$(findstring y,$(CONFIG_SAMV7_DAC0) $(CONFIG_SAMV7_DAC1)))
CSRCS += sam_dac.c
endif

ifeq ($(CONFIG_IEEE802154_MRF24J40),y)
CSRCS += sam_mrf24j40.c
endif

ifeq ($(CONFIG_IEEE802154_XBEE),y)
CSRCS += sam_xbee.c
endif

include $(TOPDIR)/configs/Board.mk
