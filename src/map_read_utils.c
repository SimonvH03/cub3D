/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/08/26 18:05:12 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void
	map_free_err_sub(
		t_point **point_map
	)
{
	int	y;

	y = 0;
	while (point_map[y] != NULL)
	{
		free(point_map[y]);
		y++;
	}
	free(point_map);
}

int
	map_free_err(
		t_map *map
	)
{
	if (map->original != NULL)
		map_free_err_sub(map->original);
	if (map->project != NULL)
		map_free_err_sub(map->project);
	if (map->polar != NULL)
		map_free_err_sub(map->polar);
	ft_printf("Error: Malloc failed\n");
	exit(EXIT_FAILURE);
}

t_point	**
	map_calloc(
		t_map *map,
		size_t size
	)
{
	void		*ptr;
	static int	count = 0;

	count++;
	ptr = (void *)malloc(size);
	if (ptr == NULL)
		map_free_err(map);
	ft_bzero(ptr, size);
	return (ptr);
}

// used by map_read()
int
	map_calloc_y(
		t_map *map
	)
{
	map->original = (t_point **)map_calloc(map,
			(map->y_max + 1) * sizeof(t_point *));
	map->project = (t_point **)map_calloc(map,
			(map->y_max + 1) * sizeof(t_point *));
	map->polar = (t_point **)map_calloc(map,
			(map->y_max + 1) * sizeof(t_point *));
	return (EXIT_SUCCESS);
}

// used by map_read()
int
	map_calloc_x(
		t_map *map,
		const int y
	)
{
	map->original[y] = (t_point *)map_calloc(map,
			(map->x_max) * sizeof(t_point));
	map->original[y + 1] = NULL;
	map->project[y] = (t_point *)map_calloc(map,
			(map->x_max) * sizeof(t_point));
	map->project[y + 1] = NULL;
	map->polar[y] = (t_point *)map_calloc(map,
			(map->x_max) * sizeof(t_point));
	map->polar[y + 1] = NULL;
	return (EXIT_SUCCESS);
}
