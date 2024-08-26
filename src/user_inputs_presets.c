/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_inputs_presets.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:31:44 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/26 18:05:12 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// from user_inputs.c / user_inputs()
// P for Parallel
// I for Isometric
void
	input_presets_flat(
		t_cub3d	*cub3d)
{
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_P))
	{
		map_iteration(cub3d->map, &map_set_original, cub3d->map);
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_I))
	{
		map_iteration(cub3d->map, &map_set_original, cub3d->map);
		cub3d->perspective = (t_perspective)
		{ISO_ALPHA, ISO_BETA, ISO_GAMMA, true};
	}
	cub3d->ballin = false;
	cub3d_center_offset(cub3d);
	cub3d->scale.diff = cub3d->scale.initial;
	cub3d->scale.total = 1;
	cub3d->spinlock = false;
}

// from user_inputs.c / user_inputs()
// O for sphere
// U for half sphere
void
	input_presets_balls(
		t_cub3d	*cub3d)
{
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_O))
	{
		cub3d->map->shape = (t_shape){S_FULL_SPHERE,
			(-2 * PI / (cub3d->map->x_max)),
			(PI / (cub3d->map->y_max - 1))};
		cub3d->perspective = (t_perspective)
		{deg_to_rad(-90), 0, deg_to_rad(90), true};
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_U))
	{
		cub3d->map->shape = (t_shape){S_HALF_SPHERE,
			(-2 * PI / (cub3d->map->x_max)),
			(0.5 * PI / (cub3d->map->y_max - 1))};
		cub3d->perspective = (t_perspective)
		{0, 0, deg_to_rad(90), true};
	}
	map_iteration(cub3d->map, &map_fill_polar, cub3d->map);
	map_iteration(cub3d->map, &map_set_polar, cub3d->map);
	cub3d_center_offset(cub3d);
	cub3d->scale.diff = cub3d->scale.sphere;
	cub3d->scale.total = 1;
	cub3d->ballin = true;
	cub3d->radius = cub3d->map->radius;
	cub3d->darksquare = cub3d->radius / sqrt(2);
}
