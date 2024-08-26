/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:49:26 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/26 18:05:12 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// used by map_init() and user_inputs_balls()
// calculates the cartesian coordinates for the points mapped onto a sphere
void
	map_fill_polar(
		void *param,
		int y,
		int x)
{
	t_map	*map;
	t_point	*point;
	t_point	temp;

	map = param;
	point = &map->original[y][x];
	temp = (t_point)
	{(map->shape.longitude * x),
		(map->shape.latitude * y),
		(map->radius + point->z),
		point->colour};
	map->polar[y][x] = (t_point)
	{((temp.z) * cos(temp.x) * sin(temp.y)),
		((temp.z) * sin(temp.x) * sin(temp.y)),
		((temp.z) * cos(temp.y)),
		temp.colour};
}

// from user_inputs_presets.c / inputs_presets_balls()
void
	map_set_polar(
		void *param,
		const int y,
		const int x)
{
	t_map	*map;

	map = param;
	map->project[y][x] = map->polar[y][x];
}

// from user_inputs_presets.c / inputs_presets_flat()
void
	map_set_original(
		void *param,
		const int y,
		const int x)
{
	t_map	*map;

	map = param;
	map->project[y][x] = map->original[y][x];
}

// from main.c / main()
int
	map_free(
		t_map *map)
{
	int	i;

	i = 0;
	while (i < map->y_max && map->project[i])
		free(map->project[i++]);
	free(map->project);
	i = 0;
	while (i < map->y_max && map->polar[i])
		free(map->polar[i++]);
	free(map->polar);
	i = 0;
	while (i < map->y_max && map->original[i])
		free(map->original[i++]);
	free(map->original);
	return (EXIT_FAILURE);
}
