/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:58:42 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/26 18:05:12 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// count elements with subject given map constraints
static int
	map_row_size(
		char *buffer)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (buffer[i])
	{
		while (buffer[i] == ' ')
			i++;
		while (buffer[i] && buffer[i] != ' ')
			i++;
		count++;
	}
	return (count);
}

// count rows with get_next_line
static int
	map_size(
		t_map *map)
{
	char	*buffer;
	int		temp_x;

	map->fd = open(map->name, O_RDONLY);
	map->y_max = 0;
	temp_x = -1;
	buffer = get_next_line(map->fd);
	while (buffer)
	{
		map->x_max = map_row_size(buffer);
		if (temp_x != -1 && temp_x != map->x_max)
		{
			ft_printf("Error: map is wonky\n");
			free(buffer);
			close(map->fd);
			return (EXIT_FAILURE);
		}
		temp_x = map->x_max;
		free(buffer);
		map->y_max++;
		buffer = get_next_line(map->fd);
	}
	close(map->fd);
	return (EXIT_SUCCESS);
}

// parse buffer, extract values with atoi, place [x,y,z] values in t_points
// make a copy at map->project
static void
	map_fill_row(
		t_map *map,
		int y,
		char *buffer)
{
	int		i;
	int		x;
	int		k;
	char	str_z[1 + 10 + 1];

	i = 0;
	x = 0;
	while (buffer[i])
	{
		k = 0;
		while (buffer[i] == ' ')
			i++;
		while (buffer[i] && buffer[i] != ' ' && k < 11)
		{
			str_z[k] = buffer[i];
			k++;
			i++;
		}
		str_z[k] = '\0';
		map->original[y][x] = (t_point)
		{x - (map->x_max / 2), y - (map->y_max / 2), ft_atoi(str_z), 0};
		map->project[y][x] = map->original[y][x];
		x++;
	}
}

// from map_init.c / map_init()
// size up the map, ft_calloc_cub3d 2D for t_points
// fill rows with each get_next_line
// make a copy at map->project to initialize projection data
int
	map_read(
		t_map *map)
{
	char	*buffer;
	int		y;

	if (map_size(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	map->fd = open(map->name, O_RDONLY);
	if (map->fd == -1)
		return (EXIT_FAILURE);
	map_calloc_y(map);
	buffer = get_next_line(map->fd);
	if (buffer == NULL)
		return (EXIT_FAILURE);
	y = 0;
	while (buffer && y < map->y_max)
	{
		map_calloc_x(map, y);
		map_fill_row(map, y, buffer);
		free(buffer);
		y++;
		buffer = get_next_line(map->fd);
	}
	close(map->fd);
	return (EXIT_SUCCESS);
}
