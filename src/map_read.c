/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:58:42 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/27 02:20:18 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static short
	map_size(
		t_scene *scene)
{
	char	*buffer;
	int		temp_x;

	scene->fd = open(scene->name, O_RDONLY);
	scene->y_max = 0;
	buffer = get_next_line(scene->fd);
	if (buffer == NULL)
		return (EXIT_FAILURE);
	while (buffer)
	{
		temp_x = ft_strlen(buffer);
		if (temp_x > scene->x_max)
			scene->x_max = temp_x;
		free(buffer);
		scene->y_max++;
		buffer = get_next_line(scene->fd);
	}
	close(scene->fd);
	return (EXIT_SUCCESS);
}

static short
	map_calloc(
		t_scene *scene)
{
	int	y;

	scene->map = (int **)malloc(sizeof(int *) * scene->y_max + 1);
	if (scene->map == NULL)
		return (EXIT_FAILURE);
	ft_bzero(scene->map, scene->y_max + 1);
	y = 0;
	while (scene->map[y] && y < scene->y_max)
	{
		scene->map[y] = (int *)malloc(sizeof(int) * scene->x_max + 1);
		if (scene->map[y] == NULL)
			return (EXIT_FAILURE);
		ft_bzero(scene->map[y], scene->x_max + 1);
		++y;
	}
	return (EXIT_SUCCESS);	
}

static short
	map_fill_row(
		t_scene *scene,
		int y,
		char *buffer)
{
	int		x;
	char	c;

	x = 0;
	while (buffer[x])
	{
		c = buffer[x];
		if (c == ' ' || c == '0')
			;
		else if (c == '1')
			scene->map[y][x] = 1;
		else if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
			pov_init(scene->camera, x, y, c);
		else
			return (EXIT_FAILURE);
		++x;
	}
	return (EXIT_SUCCESS);
}

static short
	map_fill(
		t_scene *scene)
{
	char	*buffer;
	int		y;

	scene->fd = open(scene->name, O_RDONLY);
	if (scene->fd == -1)
		return (EXIT_FAILURE);
	y = 0;
	while (buffer && y < scene->y_max)
	{
		if (map_fill_row(scene, y, buffer) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		free(buffer);
		++y;
		buffer = get_next_line(scene->fd);
	}
	if (buffer)
		free(buffer);
	close(scene->fd);
	return (EXIT_SUCCESS);
}

// from scene_init.c / scene_init()
// size up the scene, ft_calloc_cub3d 2D for t_points
// fill rows with each get_next_line
// make a copy at scene->project to initialize projection data
short
	map_read(
		t_scene *scene)
{
	if (map_size(scene) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (map_calloc(scene) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (map_fill(scene) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
