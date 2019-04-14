#
# Makefile for the Realtek network device drivers.
#
ifeq ($(NV_BUILD_CONFIGURATION_IS_COVERAGE),1)
GCOV_PROFILE_r8168.o :=y
endif

obj-$(CONFIG_R8168) += r8168.o
r8168-objs := r8168_n.o r8168_asf.o rtl_eeprom.o rtltool.o pgdrv.o
