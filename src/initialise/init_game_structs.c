/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_structs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferid <ferid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:49:26 by svan-hoo          #+#    #+#             */
/*   Updated: 2025/01/26 13:24:33 by ferid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void
	init_ui_elements(
		t_scene *scene)
{
	scene->health_bar.image = NULL;
	scene->health_bar.texture = NULL;
	scene->health_bar.current_health = 100.0f;
	scene->health_bar.max_health = 100.0f;
	scene->health_bar.width = WIDTH / 4;
	scene->health_bar.height = HEIGHT / 20;
	scene->health_bar.x_pos = 20;
	scene->health_bar.y_pos = HEIGHT - scene->health_bar.height - 80;

	scene->weapon.image = NULL;
	scene->weapon.texture = NULL;
	scene->weapon.scale = 1.0f;
	scene->weapon.enabled = true;
	scene->weapon.x_pos = WIDTH / 2;
	scene->weapon.y_pos = HEIGHT - HEIGHT / 3;

	scene->ammo_display.image = NULL;
	for (int i = 0; i < 10; i++)
		scene->ammo_display.number_textures[i] = NULL;
	scene->ammo_display.slash_texture = NULL;
	scene->ammo_display.x_pos = 0;
	scene->ammo_display.y_pos = 0;
}

void
	init_scene(
		t_scene *scene)
{
	scene->walls = NULL;
	scene->background = NULL;
	scene->name = NULL;
	scene->content = NULL;
	scene->r_content = NULL;
	scene->map = NULL;
	scene->y_max = 0;
	scene->x_max = 0;
	scene->north_texture = NULL;
	scene->east_texture = NULL;
	scene->south_texture = NULL;
	scene->west_texture = NULL;
	scene->door_texture = NULL;
	scene->door_texture2 = NULL;
	scene->player_texture = NULL;
	scene->floor = 0;
	scene->ceiling = 0;
	scene->recast = true;
	scene->doors = NULL;
	scene->door_count = 0;
	init_ui_elements(scene);
}

static short
	scene_init(
		t_scene *scene,
		char *argv_scene)
{
	init_scene(scene);
	scene->player_texture = &mlx_load_xpm42(PLAYER_ICON_PATH)->texture;
	if (scene->player_texture == NULL)
		return (EXIT_FAILURE);
	scene->name = argv_scene;
	if (get_content(scene) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	scene->door_texture = &mlx_load_xpm42(DOOR_TEXTURE_PATH)->texture;
	if (scene->door_texture == NULL)
		return (EXIT_FAILURE);
	scene->door_texture2 = &mlx_load_xpm42(DOOR_TEXTURE_PATH2)->texture;
	if (scene->door_texture2 == NULL)
		return (EXIT_FAILURE);
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
