/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_images.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferid <ferid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2025/01/27 16:24:23 by ferid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static short
	new_images_scene(
		mlx_t *mlx,
		t_scene *scene)
{
	scene->background = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (scene->background == NULL)
		return (EXIT_FAILURE);
	scene->walls = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (scene->walls == NULL)
		return (EXIT_FAILURE);
	scene->health_bar.width = 200;
	scene->health_bar.height = 10;
	scene->health_bar.x_pos = WIDTH - scene->health_bar.width - 20;
	scene->health_bar.y_pos = 20;
	scene->health_bar.image = mlx_new_image(mlx, scene->health_bar.width, scene->health_bar.height);
	if (scene->health_bar.image == NULL)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(mlx, scene->background, 0, 0) < 0)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(mlx, scene->walls, 0, 0) < 0)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(mlx, scene->health_bar.image, scene->health_bar.x_pos, scene->health_bar.y_pos) < 0)
		return (EXIT_FAILURE);
	if (init_weapon(mlx, scene) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static short
	new_images_minimap(
		mlx_t *mlx,
		mlx_texture_t *player,
		t_minimap *minimap)
{
	minimap->walls = mlx_new_image(mlx, minimap->side, minimap->side);
	if (minimap->walls == NULL)
		return (EXIT_FAILURE);
	minimap->player = mlx_texture_to_image(mlx, player);
	if (minimap->player == NULL)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(mlx, minimap->walls,
			mlx->width - minimap->side * 1.2,
			mlx->height - minimap->side * 1.2) < 0)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(mlx, minimap->player,
			minimap->walls->instances[0].x + minimap->radius
			- minimap->player->width / 2,
			minimap->walls->instances[0].y + minimap->radius
			- minimap->player->height / 2) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static short
	new_images_map(
		mlx_t *mlx,
		t_map *map)
{
	map->walls = mlx_new_image(mlx, mlx->width, mlx->height);
	if (map->walls == NULL)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(mlx, map->walls, 0, 0) < 0)
		return (EXIT_FAILURE);
	map->player = mlx_new_image(mlx,
			(uint32_t)map->block_size, (uint32_t)map->block_size);
	if (map->player == NULL)
		return (EXIT_FAILURE);
	map->x_offset = mlx->width - map->r_scene->x_max * map->block_size;
	map->y_offset = mlx->height - map->r_scene->y_max * map->block_size;
	map->x_offset -= map->player->width;
	map->y_offset -= map->player->height;
	map->x_offset /= 2;
	map->y_offset /= 2;
	if (mlx_image_to_window(mlx, map->player,
			map->x_offset + map->r_scene->camera.pos_x * map->block_size,
			map->y_offset + map->r_scene->camera.pos_y * map->block_size) < 0)
		return (EXIT_FAILURE);
	map->player->enabled = false;
	map->walls->enabled = false;
	return (EXIT_SUCCESS);
}

short
	init_game_images(
		mlx_t *mlx,
		t_window *window)
{
	if (new_images_scene(mlx, &window->scene) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (new_images_minimap(mlx, window->scene.player_texture, &window->minimap) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (new_images_map(mlx, &window->map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	draw_scene_background(&window->scene);
	draw_minimap_circle_overlay(&window->minimap);
	if (init_crosshair(mlx, &window->scene) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (init_weapon(mlx, &window->scene) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	draw_map_walls(&window->map);
	window->fps = mlx_put_string(mlx, "0000", WIDTH / 2 - 50, 100);
	return (EXIT_SUCCESS);
}

short
    init_crosshair(
        mlx_t *mlx,
        t_scene *scene)
{
    xpm_t* crosshair_xpm;

    crosshair_xpm = mlx_load_xpm42("scenes/textures/crosshair.xpm42");
    if (!crosshair_xpm)
        return (EXIT_FAILURE);
    scene->crosshair_texture = &crosshair_xpm->texture;

    // Create crosshair image
    scene->crosshair = mlx_new_image(mlx, scene->crosshair_texture->width, scene->crosshair_texture->height);
    if (!scene->crosshair)
        return (EXIT_FAILURE);

    // Position crosshair at center of screen
    if (mlx_image_to_window(mlx, scene->crosshair, 
        (WIDTH - scene->crosshair_texture->width) / 2,
        (HEIGHT - scene->crosshair_texture->height) / 2) < 0)
        return (EXIT_FAILURE);

    return (EXIT_SUCCESS);
}

