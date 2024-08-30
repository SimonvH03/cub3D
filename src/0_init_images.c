/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_init_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/08/30 14:20:10 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static short
	new_images_minimap(
		t_window *window,
		t_minimap *minimap)
{
	minimap->walls = mlx_new_image(window->mlx,
		minimap->side, minimap->side);
	if (minimap->walls == NULL)
		return (EXIT_FAILURE);
	// minimap->player = mlx_new_image(window->mlx,
	// 	minimap->side / 18, minimap->side / 18);
	// if (minimap->player == NULL)
	// 	return (EXIT_FAILURE);
	if (mlx_image_to_window(window->mlx, minimap->walls,
		window->mlx->width - minimap->side,
		window->mlx->height - minimap->side) < 0)
		return (EXIT_FAILURE);
	// if (mlx_image_to_window(window->mlx, minimap->player,
	// 	window->mlx->width - minimap->side * 1/2,
	// 	window->mlx->height - minimap->side * 1/2) < 0)
	// 	return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

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
	scene->north_texture = mlx_load_png("png/wall.png");
	if (scene->north_texture == NULL)
		return (EXIT_FAILURE);
	scene->east_texture = scene->north_texture;
	scene->south_texture = scene->north_texture;
	scene->west_texture = scene->north_texture;
	if (mlx_image_to_window(window->mlx, scene->background, 0, 0) < 0)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(window->mlx, scene->walls, 0, 0) < 0)
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
	draw_scene_background(&window->scene);
	draw_minimap_border_overlay(&window->minimap);
	// draw_minimap_player(&window->minimap);
	// init_menu();
	// init_hud();
	// init_map();
	return (EXIT_SUCCESS);
}
