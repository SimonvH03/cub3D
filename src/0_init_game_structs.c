/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_init_game_structs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:49:26 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/15 16:15:29 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static short
	scene_init(
		t_scene *scene,
		char *argv_scene)
{
	scene->player_texture = &mlx_load_xpm42(PLAYER_ICON_PATH)->texture;
	if (scene->player_texture == NULL)
		return (EXIT_FAILURE);
	scene->name = argv_scene;
	if (get_content(scene) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	scene->north_texture = NULL;
	scene->east_texture = NULL;
	scene->south_texture = NULL;
	scene->west_texture = NULL;
	read_elements(scene);
	if (scene->north_texture == NULL || scene->east_texture == NULL
		|| scene->south_texture == NULL || scene->west_texture == NULL)
		error_exit(mlx_errno, EINVAL, "missing scene.cub texture path");
	if (read_map(scene) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	scene->recast = true;
	return (EXIT_SUCCESS);
}

static short
	minimap_init(
		t_minimap *minimap,
		t_window *window)
{
	minimap->scene = &window->scene;
	minimap->side = window->mlx->height / 3;
	minimap->radius = minimap->side / 2;
	minimap->circle_overlay = malloc(sizeof(uint32_t)
			* (pow(minimap->side, 2) + 1) + 1);
	if (minimap->circle_overlay == NULL)
		return (EXIT_FAILURE);
	minimap->scale = minimap->side / 6 * minimap->scene->camera.aspect_ratio;
	minimap->enabled = true;
	return (EXIT_SUCCESS);
}

static short
	map_init(
		t_map *map,
		t_window *window)
{
	map->scene = &window->scene;
	map->enabled = false;
	map->scale = ft_max_float(
			(map->scene->x_max + 2) / (float)window->mlx->width,
			(map->scene->y_max + 2) / (float)window->mlx->height);
	return (EXIT_SUCCESS);
}

static short
	window_init(
		t_window *window)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_set_setting(MLX_FULLSCREEN, false);
	mlx_set_setting(MLX_MAXIMIZED, false);
	mlx_set_setting(MLX_DECORATED, true);
	mlx_set_setting(MLX_HEADLESS, false);
	window->mlx = mlx_init(WIDTH, HEIGHT, WINDOW_TITLE, false);
	if (window->mlx == NULL)
		return (EXIT_FAILURE);
	window->view = MENU;
	window->time = 0;
	window->deltatime = 0;
	return (EXIT_SUCCESS);
}

short
	init_game_structs(
		t_window *window,
		char *argv_scene)
{
	if (window_init(window) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (scene_init(&window->scene, argv_scene) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (minimap_init(&window->minimap, window) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (map_init(&window->map, window) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
