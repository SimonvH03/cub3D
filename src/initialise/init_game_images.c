/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_images.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/09/18 22:16:43 by svan-hoo         ###   ########.fr       */
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
	if (mlx_image_to_window(mlx, scene->background, 0, 0) < 0)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(mlx, scene->walls, 0, 0) < 0)
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
	if (new_images_minimap(mlx, window->scene.player_texture,
			&window->minimap) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (new_images_map(mlx, &window->map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	draw_scene_background(&window->scene);
	draw_minimap_circle_overlay(&window->minimap);
	draw_map_walls(&window->map);
	window->fps = mlx_put_string(mlx, "0000", WIDTH / 2 - 50, 100);
	return (EXIT_SUCCESS);
}
