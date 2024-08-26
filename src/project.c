/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:59:22 by simon             #+#    #+#             */
/*   Updated: 2024/08/26 18:05:12 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// from main.c / loop_hooks()
// if the user inputs changed stuff, we recalculate the position of our points
void
	project(
		void *param)
{
	t_cub3d	*cub3d;

	cub3d = param;
	if (cub3d->perspective.reproject == true)
	{
		map_iteration(cub3d->map, &cub3d_rotate, cub3d);
		cub3d->perspective = (t_perspective){0, 0, 0, false};
	}
	if (cub3d->precalc.reproject == true)
	{
		map_iteration(cub3d->map, &cub3d_rotate_optimized, cub3d);
		if (cub3d->spinlock == false)
			cub3d->precalc = (t_precalc){0, 0, 0, 1, false};
	}
	if (cub3d->scale.diff != 1)
	{
		cub3d->offset.x *= cub3d->scale.diff;
		cub3d->offset.y *= cub3d->scale.diff;
		cub3d->radius *= cub3d->scale.diff;
		cub3d->darksquare *= cub3d->scale.diff;
		map_iteration(cub3d->map, &cub3d_scale, cub3d);
		cub3d->scale.diff = 1;
	}
}
