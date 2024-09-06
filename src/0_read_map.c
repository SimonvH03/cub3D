/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_read_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:58:42 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/05 19:41:56 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static short
	map_size(
		t_scene *scene)
{
	int		temp_x;

	scene->y_max = 0;
	scene->x_max = 0;
	while (scene->content[scene->y_max])
	{
		temp_x = ft_strlen(scene->content[scene->y_max]);
		if (scene->content[scene->y_max][temp_x - 1] == '\n')
			--temp_x;
		if (temp_x > scene->x_max)
			scene->x_max = temp_x;
		++scene->y_max;
	}
	return (EXIT_SUCCESS);
}

static short
	map_fill_row(
		t_scene *scene,
		int y,
		char *line)
{
	int		x;

	x = 0;
	while (line[x] && line[x] != '\n')
	{
		if (line[x] == ' ')
			scene->map[y][x] = -1;
		else if (line[x] == '1'|| line[x] == '0')
			scene->map[y][x] = line[x] - 48;
		else if (line[x] == 'N' || line[x] == 'E'
			|| line[x] == 'S' || line[x] == 'W')
		{
			scene->map[y][x] = 0;
			camera_init(&scene->camera, y, x, line[x]);
		}
		else
			return (EXIT_FAILURE);
		++x;
	}
	while (x < scene->x_max)
	{
		scene->map[y][x] = -1;
		++x;
	}
	return (EXIT_SUCCESS);
}

short
	read_map(
		t_scene *scene)
{
	int	y;

	if (map_size(scene) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	scene->map = (int **)ft_calloc(scene->y_max + 1, sizeof(int *));
	if (scene->map == NULL)
		return (EXIT_FAILURE);
	y = 0;
	while (y < scene->y_max)
	{
		scene->map[y] = (int *)ft_calloc(scene->x_max, sizeof(int));
		if (scene->map[y] == NULL)
			return (EXIT_FAILURE);
		if (map_fill_row(scene, y, scene->content[y]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		++y;
	}
	return (EXIT_SUCCESS);
}
