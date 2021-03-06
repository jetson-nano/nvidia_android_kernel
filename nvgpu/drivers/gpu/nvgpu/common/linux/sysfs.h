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
#ifndef NVGPU_SYSFS_H
#define NVGPU_SYSFS_H

/*  limit upper bound for MAX_SUBMIT_BOOST_TIME to 10 seconds */
#define MAX_SUBMIT_BOOST_TIME	10000

struct device;

int nvgpu_create_sysfs(struct device *dev);
void nvgpu_remove_sysfs(struct device *dev);

#endif
