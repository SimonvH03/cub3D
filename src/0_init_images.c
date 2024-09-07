/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_init_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/09/07 03:55:26 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static short
	new_images_scene(
		t_window *window,
		t_scene *scene)
{
	scene->background = mlx_new_image(window->mlx, WIDTH, HEIGHT);
	if (scene->background == NULL)
		return (EXIT_FAILURE);
	scene->walls = mlx_new_image(window->mlx, WIDTH, HEIGHT);
	if (scene->walls == NULL)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(window->mlx, scene->background, 0, 0) < 0)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(window->mlx, scene->walls, 0, 0) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static short
	new_images_minimap(
		t_window *window,
		t_minimap *minimap)
{
	xpm_t	*tempx;

	minimap->walls = mlx_new_image(window->mlx,
		minimap->side, minimap->side);
	if (minimap->walls == NULL)
		return (EXIT_FAILURE);
	tempx = mlx_load_xpm42("./textures/player.xpm42");
	if (tempx == NULL)
		return (EXIT_FAILURE);
	minimap->player = mlx_texture_to_image(window->mlx, &tempx->texture);
	if (minimap->player == NULL)
		return (EXIT_FAILURE);
	mlx_delete_xpm42(tempx);
	if (mlx_image_to_window(window->mlx, minimap->walls,
		window->mlx->width - minimap->side,
		window->mlx->height - minimap->side) < 0)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(window->mlx, minimap->player,
		window->mlx->width - minimap->c_offset
			- minimap->player->width / 2,
		window->mlx->height - minimap->c_offset
			- minimap->player->height / 2) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static short
	new_images_map(
		t_window *window,
		t_map *map)
{
	map->walls = mlx_new_image(window->mlx, map->side, map->side);
	if (map->walls == NULL)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(window->mlx, map->walls,
		(window->mlx->width - map->side / 2),
		(window->mlx->height - map->side / 2)) < 0)
		return (EXIT_FAILURE);
	map->player = mlx_new_image(window->mlx, map->side / 42, map->side / 42);
	if (map->player == NULL)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(window->mlx, map->player,
		(window->mlx->width / 2),
		(window->mlx->height / 2)) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

short
	init_images(
		t_window *window)
{
	if (new_images_scene(window, &window->scene) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (new_images_minimap(window, &window->minimap) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (new_images_map(window, &window->map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	draw_scene_background(&window->scene);
	draw_minimap_circle_overlay(&window->minimap);
	// draw_minimap_player(&window->minimap);
	// init_menu();
	// init_hud();
	return (EXIT_SUCCESS);
}
