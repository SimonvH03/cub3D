/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iteration.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:47:59 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/26 18:05:12 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// used by map_init(), project(), keyhook(), draw() and user_inputs_presets.c
// applies the function *f(whatever) to the whole map(s)
void
	map_iteration(
		t_map *map,
		mapi_func *function,
		void *param)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->y_max)
	{
		x = 0;
		while (x < map->x_max)
		{
			function(param, y, x);
			x++;
		}
		y++;
	}
}

// CHECKLIST
// void	cub3d_draw(t_cub3d *cub3d);
// void	cub3d_colour(t_cub3d *cub3d);
// void	cub3d_project_optimized(t_cub3d *cub3d);
// void	cub3d_project(t_cub3d *cub3d);
// void	cub3d_scale(t_cub3d *cub3d);
// void	map_set_original(t_map *map);
// void	map_fill_polar(t_map *map);
// void	map_set_polar(t_map *map);
// void	map_find_z_min_max(t_map *map);
// get destroyed lol
