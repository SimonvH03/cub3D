/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_inputs_keyscroll.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:05:56 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/26 23:20:46 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// from main.c / loop_hooks()
void
	keyhook(
		mlx_key_data_t keydata,
		void *param)
{
	t_cub3d	*cub3d;

	cub3d = param;
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		cub3d->spinlock = (!cub3d->spinlock);
		cub3d->cosin = (t_cosin){cos(cub3d->speed), sin(cub3d->speed)};
	}
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
	{
		cub3d->scene->palette = scene_cycle_palettes(cub3d->scene);
		if (!cub3d->scene->isearth && cub3d->scene->palette.nr == P_EARTH_NR)
			cub3d->scene->palette = scene_cycle_palettes(cub3d->scene);
		scene_iteration(cub3d->scene, &scene_colour, cub3d->scene);
	}
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	{
		cub3d_center_offset(cub3d);
		cub3d->scale.diff = 1 / cub3d->scale.total;
		cub3d->scale.total = 1;
	}
	if (keydata.key == MLX_KEY_T && keydata.action == MLX_PRESS)
		cub3d->precalc.sign *= -1;
	if (keydata.key == MLX_KEY_H && keydata.action == MLX_PRESS)
		cub3d->horizon = !cub3d->horizon;
}

// from main.c / loop_hooks()
void
	scrollhook(
		double xdelta,
		double ydelta,
		void *param)
{
	t_cub3d	*cub3d;

	cub3d = param;
	(void)xdelta;
	if (ydelta)
	{
		cub3d->scale.diff *= 1 + (ydelta / 10);
		cub3d->scale.total *= 1 + (ydelta / 10);
	}
}
