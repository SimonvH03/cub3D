/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_init_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/08/28 22:00:04 by simon            ###   ########.fr       */
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

	x = 0;
	while (x < image->width)
	{
		y = 0;
		while (y < half_height)
		{
			mlx_put_pixel(image, x, y, scene->ceiling);
			mlx_put_pixel(image, x, half_height + y, scene->floor);
			++y;
		}
		++x;
	}
}

short
	init_images(
		t_window *window)
{
	window->scene.background = mlx_new_image(window->mlx, WIDTH, HEIGHT);
	if (window->scene.background == NULL)
		return (EXIT_FAILURE);
	window->scene.walls = mlx_new_image(window->mlx, WIDTH, HEIGHT);
	if (window->scene.walls == NULL)
		return (EXIT_FAILURE);
	draw_background(&window->scene, window->scene.background);
	if (mlx_image_to_window(window->mlx, window->scene.background, 0, 0) < 0)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(window->mlx, window->scene.walls, 0, 0) < 0)
		return (EXIT_FAILURE);
	// init_menu();
	// init_hud();
	// init_map();
	// init_minimap();
	return (EXIT_SUCCESS);
}
