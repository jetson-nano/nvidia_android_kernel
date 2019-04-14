/*
 * Copyright (c) 2017, NVIDIA CORPORATION.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* TODO set all define values correctly, copied from ov5693*/
#ifndef __IMX318_H__
#define __IMX318_H__

#include <media/nvc.h>
#include <media/nvc_image.h>

#define IMX318_IOCTL_SET_MODE               _IOW('o', 1, struct imx318_mode)
#define IMX318_IOCTL_SET_FRAME_LENGTH       _IOW('o', 2, __u32)
#define IMX318_IOCTL_SET_COARSE_TIME        _IOW('o', 3, __u32)
#define IMX318_IOCTL_SET_GAIN               _IOW('o', 4, __u16)
#define IMX318_IOCTL_GET_STATUS             _IOR('o', 5, __u8)
#define IMX318_IOCTL_SET_BINNING            _IOW('o', 6, __u8)
#define IMX318_IOCTL_TEST_PATTERN           _IOW('o', 7, \
						 enum imx318_test_pattern)
#define IMX318_IOCTL_SET_GROUP_HOLD         _IOW('o', 8, struct imx318_ae)
/* operating mode can be either stereo , leftOnly or rightOnly */
#define IMX318_IOCTL_SET_CAMERA_MODE        _IOW('o', 10, __u32)
#define IMX318_IOCTL_SYNC_SENSORS           _IOW('o', 11, __u32)
#define IMX318_IOCTL_GET_FUSEID             _IOR('o', 12, struct nvc_fuseid)
#define IMX318_IOCTL_SET_CAL_DATA           _IOW('o', 15, \
						struct imx318_cal_data)
#define IMX318_IOCTL_GET_EEPROM_DATA        _IOR('o', 20, __u8 *)
#define IMX318_IOCTL_SET_EEPROM_DATA        _IOW('o', 21, __u8 *)
#define IMX318_IOCTL_GET_CAPS               _IOR('o', 22, struct nvc_imager_cap)
#define IMX318_IOCTL_SET_POWER              _IOW('o', 23, __u32)

#define IMX318_INVALID_COARSE_TIME  -1

#define IMX318_EEPROM_ADDRESS		0x50
#define IMX318_EEPROM_SIZE		1024
#define IMX318_EEPROM_STR_SIZE		(IMX318_EEPROM_SIZE * 2)
#define IMX318_EEPROM_BLOCK_SIZE	(1 << 8)
#define IMX318_EEPROM_NUM_BLOCKS \
	(IMX318_EEPROM_SIZE / IMX318_EEPROM_BLOCK_SIZE)

/* Incorrect data, cannot find fuse ID in documentation */
#define IMX318_FUSE_ID_START_ADDR	0x0000 /* manufacturing ID */
#define IMX318_FUSE_ID_BANK	0
#define IMX318_FUSE_ID_SIZE		4
#define IMX318_FUSE_ID_STR_SIZE	(IMX318_FUSE_ID_SIZE * 2)

struct imx318_mode {
	int res_x;
	int res_y;
	int fps;
	__u32 frame_length;
	__u32 coarse_time;
	__u32 coarse_time_short;
	__u16 gain;
	__u8 hdr_en;
};

struct imx318_ae {
	__u32 frame_length;
	__u8  frame_length_enable;
	__u32 coarse_time;
	__u32 coarse_time_short;
	__u8  coarse_time_enable;
	__s32 gain;
	__u8  gain_enable;
};

struct imx318_fuseid {
	__u32 size;
	__u8  id[16];
};

struct imx318_hdr {
	__u32 coarse_time_long;
	__u32 coarse_time_short;
};

struct imx318_otp_bank {
	__u32 id;
	__u8  buf[16];
};

struct imx318_cal_data {
	int loaded;
	int rg_ratio;
	int bg_ratio;
	int rg_ratio_typical;
	int bg_ratio_typical;
	__u8 lenc[62];
};

/* See notes in the nvc.h file on the GPIO usage */
enum imx318_gpio_type {
	IMX318_GPIO_TYPE_PWRDN = 0,
	IMX318_GPIO_TYPE_RESET,
};

struct imx318_eeprom_data {
	struct i2c_client *i2c_client;
	struct i2c_adapter *adap;
	struct i2c_board_info brd;
	struct regmap *regmap;
};

struct imx318_power_rail {
	struct regulator *dvdd;
	struct regulator *avdd;
	struct regulator *dovdd;
};

struct imx318_regulators {
	const char *avdd;
	const char *dvdd;
	const char *dovdd;
};

struct imx318_platform_data {
	unsigned int cfg;
	unsigned int num;
	const char *dev_name;
	unsigned int gpio_count; /* see nvc.h GPIO notes */
	struct nvc_gpio_pdata *gpio; /* see nvc.h GPIO notes */
	struct nvc_imager_static_nvc *static_info;
	bool use_vcm_vdd;
	int (*probe_clock)(unsigned long);
	int (*power_on)(struct imx318_power_rail *);
	int (*power_off)(struct imx318_power_rail *);
	const char *mclk_name;
	struct nvc_imager_cap *cap;
	struct imx318_regulators regulators;
	bool has_eeprom;
	bool use_cam_gpio;
};

#endif  /* __IMX318_H__ */
