/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_game.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:49:26 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/05/12 18:17:29 by svan-hoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int
	get_content(
		char ***dest,
		const char *input_file)
{
	char	*buffer;
	int		fd;

	fd = open(input_file, O_RDONLY);
	if (fd == -1)
		return (set_error(CUB_INVFILE));
	buffer = ft_get_next_line(fd);
	if (buffer == NULL)
		return (set_error(CUB_LIBFTFAIL));
	*dest = NULL;
	while (buffer != NULL)
	{
		if (buffer[0] != '\n')
		{
			if (buffer[ft_strlen(buffer) - 1] == '\n')
				buffer[ft_strlen(buffer) - 1] = '\0';
			*dest = ft_arrcat(*dest, buffer);
			if (*dest == NULL)
				return (set_error(CUB_MEMFAIL));
		}
		else
			free(buffer);
		buffer = ft_get_next_line(fd);
	}
	return (RETURN_SUCCESS);
}

static int
	parse_input_file(
		t_window *window,
		t_scene *scene,
		const char *input_file)
{
	char	**content_start;
	char	**content_progress;

	if (get_content(&content_start, input_file) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	content_progress = content_start;
	if (read_elements(window, scene, &content_progress) != RETURN_SUCCESS)
	{
		ft_arrclear((void **)content_start);
		return (RETURN_FAILURE);
	}
	if (scene->walls.doorface == NULL || scene->walls.doorside == NULL)
		return (set_error(CUB_DATAFAIL));
	if (scene->walls.north == NULL || scene->walls.east == NULL
		|| scene->walls.south == NULL || scene->walls.west == NULL)
		return (set_error(CUB_NOTEX));
	if (scene->floor_clr == (uint32_t)0 || scene->ceiling_clr == (uint32_t)0)
		return (set_error(CUB_NOCLR));
	if (read_tilemap(&scene->grid, content_progress) != RETURN_SUCCESS)
	{
		ft_arrclear((void **)content_start);
		return (RETURN_FAILURE);
	}
	ft_arrclear((void **)content_start);
	return (RETURN_SUCCESS);
}

int
	init_game(
		t_window *window,
		t_scene *scene,
		const char *input_file)
{
	mlx_t	*mlx;

	mlx = window->mlx;
	window->player.camera.aspect_ratio = mlx->width / (float)mlx->height;
	window->player.camera.height_offset = mlx->height / 2;
	if (parse_input_file(window, scene, input_file) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	if (gridmap_iter(&scene->grid, perimeter_check, NULL) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	if (init_doors(&scene->grid) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	if (init_player(&window->player, &scene->grid) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	scene->walls.image = mlx_new_image(mlx, mlx->width, mlx->height);
	if (scene->walls.image == NULL)
		return (set_error(CUB_MLXFAIL));
	if (mlx_image_to_window(mlx, scene->walls.image, 0, 0) < 0)
		return (set_error(CUB_MLXFAIL));
	if (init_hud(window, &window->hud) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}
