/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_colour.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/08/26 18:05:12 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static uint32_t
	map_earth_colour(
		const t_map *map,
		const t_point *point)
{
	const double	current_z = point->z;

	if (current_z < 0)
		return (gradient(current_z / map->z_min,
				C_EARTH_SEA, C_EARTH_DEEP_SEA));
	if (point->y > map->y_max * 0.39203539823)
		return (C_EARTH_SNOW);
	if (current_z < (map->z_max * 0.65))
		return (gradient(current_z / (map->z_max * 0.65),
				C_EARTH_LAND, C_EARTH_MOUNTAIN));
	else
		return (gradient(current_z / map->z_max,
				C_EARTH_MOUNTAIN, C_EARTH_SNOW));
}

static uint32_t
	map_point_colour(
		const t_map *map,
		const t_point *point)
{
	const double	relative_height = point->z - map->z_min;
	double			ratio;

	if (map->total_height == 0)
		return (map->palette.low);
	ratio = relative_height / map->total_height;
	if (ratio <= 0.5)
		return (gradient(ratio * 2,
				map->palette.low, map->palette.mid));
	else
		return (gradient((ratio - 0.5) * 2,
				map->palette.mid, map->palette.high));
}

// from map_init.c / map_init()
void
	map_colour(
		void *param,
		const int y,
		const int x)
{
	t_map	*map;
	t_point	*point;

	map = param;
	point = &map->original[y][x];
	if (map->palette.nr == P_EARTH_NR)
		point->colour = map_earth_colour(map, point);
	else
		point->colour = map_point_colour(map, point);
	map->project[y][x].colour = point->colour;
	map->polar[y][x].colour = point->colour;
}
