/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:49:26 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/26 18:05:12 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// inspects the argument given to determine whether map is likely earth
static int
	map_is_earth(
		const char *map_name)
{
	int		name_length;
	char	*search_name;

	if (map_name == NULL)
		return (false);
	name_length = ft_strlen(map_name);
	search_name = ft_strdup(map_name);
	if (search_name == NULL)
		return (false);
	name_length = ft_str_toupper(search_name);
	if (ft_strnstr(search_name, "WORLD", name_length)
		|| ft_strnstr(search_name, "GLOBE", name_length)
		|| ft_strnstr(search_name, "EARTH", name_length)
		|| ft_strnstr(search_name, "WERELD", name_length))
	{
		free(search_name);
		return (true);
	}
	free(search_name);
	return (false);
}

// finds minimum and maximum z (height) value in the map
static void
	map_find_z_min_max(
		void *param,
		const int y,
		const int x)
{
	t_map	*map;
	int		z_val;

	map = param;
	z_val = map->original[y][x].z;
	if (z_val < map->z_min)
		map->z_min = z_val;
	if (z_val > map->z_max)
		map->z_max = z_val;
}

// from main.c / main()
int
	map_init(
		t_map *map,
		char *map_name)
{
	map->original = NULL;
	map->project = NULL;
	map->polar = NULL;
	map->palette = (t_palette)
	{P_RGB_NR, C_RGB_BACK, C_RGB_LOW, C_RGB_MID, C_RGB_HIGH};
	if (map_is_earth(map_name) == true)
		map->palette = (t_palette){P_EARTH_NR, C_EARTH_BACK, 0, 0, 0};
	map->isearth = (bool)(map->palette.nr == P_EARTH_NR);
	map->name = map_name;
	map->fd = 0;
	if (map_read(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	map->z_min = 0;
	map->z_max = 0;
	map_iteration(map, &map_find_z_min_max, map);
	map->total_height = map->z_max - map->z_min;
	map->radius = (map->total_height) * 10;
	if (map->radius == 0)
		map->radius = 1;
	map->shape = (t_shape)
	{S_FULL_SPHERE, -2 * PI / (map->x_max), PI / (map->y_max - 1)};
	map_iteration(map, &map_fill_polar, map);
	map_iteration(map, &map_colour, map);
	return (EXIT_SUCCESS);
}
