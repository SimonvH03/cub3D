/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_init_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/08/29 22:43:32 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static short
	new_images_minimap(
		t_window *window,
		t_minimap *minimap)
{
	minimap->walls = mlx_new_image(window->mlx,
		minimap->width, minimap->height);
	if (minimap->walls == NULL)
		return (EXIT_FAILURE);
	minimap->player = mlx_new_image(window->mlx,
		minimap->width, minimap->height);
	if (minimap->player == NULL)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(window->mlx, minimap->walls,
		window->mlx->width - minimap->width,
		window->mlx->height - minimap->height) < 0)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(window->mlx, minimap->player,
		window->mlx->width - minimap->width,
		window->mlx->height - minimap->height) < 0)
		return (EXIT_FAILURE);
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
	// init_menu();
	// init_hud();
	// init_map();
	return (EXIT_SUCCESS);
}
