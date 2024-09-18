/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_structs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:49:26 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/18 22:11:14 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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
	scene->camera.movement_speed = 0;
	read_elements(scene);
	if (scene->north_texture == NULL || scene->east_texture == NULL
		|| scene->south_texture == NULL || scene->west_texture == NULL)
		error_exit(mlx_errno, EINVAL, "missing scene.cub texture path");
	if (read_map(scene) == EXIT_FAILURE || scene->camera.movement_speed == 0)
		return (EXIT_FAILURE);
	scene->recast = true;
	return (EXIT_SUCCESS);
}

static short
	minimap_init(
		t_minimap *minimap,
		mlx_t *mlx)
{
	minimap->side = ft_min_float(mlx->height, mlx->width) / 3;
	minimap->radius = minimap->side / 2;
	minimap->circle_overlay = malloc(sizeof(uint32_t)
			* (pow(minimap->side, 2) + 1) + 1);
	if (minimap->circle_overlay == NULL)
		return (EXIT_FAILURE);
	minimap->block_size = (minimap->side / 6)
		* minimap->r_scene->camera.aspect_ratio;
	minimap->enabled = true;
	return (EXIT_SUCCESS);
}

static short
	map_init(
		t_map *map,
		mlx_t *mlx)
{
	map->enabled = false;
	map->block_size = ft_min_float(
			mlx->height / (map->r_scene->y_max + 2),
			mlx->width / (map->r_scene->x_max + 2));
	return (EXIT_SUCCESS);
}

short
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
	return (EXIT_SUCCESS);
}

short
	init_game_structs(
		mlx_t *mlx,
		t_window *window,
		char *argv_scene)
{
	if (scene_init(&window->scene, argv_scene) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	window->minimap.r_scene = &window->scene;
	window->map.r_scene = &window->scene;
	if (minimap_init(&window->minimap, mlx) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (map_init(&window->map, mlx) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
