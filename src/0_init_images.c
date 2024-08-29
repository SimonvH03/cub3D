/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_init_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/08/29 18:21:51 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void
	draw_background(
		t_scene *scene,
		mlx_image_t *image)
{
	uint32_t		y;
	uint32_t		x;
	const uint32_t	half_height = image->height / 2;
	uint32_t		colour;

	x = 0;
	while (x < image->width)
	{
		y = 0;
		while (y < half_height)
		{
			colour = gradient(y / (float)half_height, scene->ceiling, scene->floor);
			mlx_put_pixel(image, x, half_height - y, colour);
			mlx_put_pixel(image, x, half_height + y, colour);
			++y;
		}
		++x;
	}
}

void
	draw_minimap(
		t_scene *scene,
		mlx_image_t *image)
{
	uint32_t		y;
	uint32_t		x;
	uint32_t		colour;

	x = 0;
	while (x < image->width)
	{
		y = 0;
		while (y < image->height)
		{
			colour = 0x000000FF;
			mlx_put_pixel(image, x, y, colour);
			++y;
		}
		++x;
	}
}

static short
	new_images(
		t_window *window)
{
	window->scene.background = mlx_new_image(window->mlx, WIDTH, HEIGHT);
	if (window->scene.background == NULL)
		return (EXIT_FAILURE);
	window->scene.walls = mlx_new_image(window->mlx, WIDTH, HEIGHT);
	if (window->scene.walls == NULL)
		return (EXIT_FAILURE);
	window->minimap.border = mlx_new_image(window->mlx, WIDTH / 8, HEIGHT / 8);
	if (window->minimap.border == NULL)
		return (EXIT_FAILURE);
	window->minimap.walls = mlx_new_image(window->mlx, WIDTH / 8, HEIGHT / 8);
	if (window->minimap.walls == NULL)
		return (EXIT_FAILURE);
	window->minimap.player = mlx_new_image(window->mlx, WIDTH / 8, HEIGHT / 8);
	if (window->minimap.player == NULL)
		return (EXIT_FAILURE);
}

short
	init_images(
		t_window *window)
{
	if (new_images(window) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	draw_background(&window->scene, window->scene.background);
	draw_minimap(&window->minimap, &window->minimap);
	// init_menu();
	// init_hud();
	// init_map();
	if (mlx_image_to_window(window->mlx, window->scene.background, 0, 0) < 0)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(window->mlx, window->scene.walls, 0, 0) < 0)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(window->mlx, window->minimap.border, WIDTH * 0.8, HEIGHT * 0.8) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
