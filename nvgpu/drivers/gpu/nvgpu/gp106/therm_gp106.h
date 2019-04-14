/*
 * general thermal control structures & definitions
 *
 * Copyright (c) 2016-2017, NVIDIA CORPORATION.  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef NVGPU_THERM_GP106_H
#define NVGPU_THERM_GP106_H

struct gk20a;

void gp106_get_internal_sensor_limits(s32 *max_24_8, s32 *min_24_8);
int gp106_get_internal_sensor_curr_temp(struct gk20a *g, u32 *temp_f24_8);
#ifdef CONFIG_DEBUG_FS
void gp106_therm_debugfs_init(struct gk20a *g);
#endif
int gp106_elcg_init_idle_filters(struct gk20a *g);
u32 gp106_configure_therm_alert(struct gk20a *g, s32 curr_warn_temp);

#endif
