/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_draw_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/08/30 03:17:13 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void
	draw_minimap_border_overlay(
		t_minimap *minimap)
{
	uint32_t			y;
	uint32_t			x;

	x = 0;
	while (x < minimap->side)
	{
		y = 0;
		while (y < minimap->side)
		{
			if (is_in_circle(minimap->c_offset, minimap->c_offset,
				minimap->radius, x, y) == false)
				mlx_put_pixel(minimap->walls, x, y, C_TRANSPARENT);
			else if (is_in_circle(minimap->c_offset, minimap->c_offset,
				minimap->radius * 15/16, x, y) == false)
				mlx_put_pixel(minimap->walls, x, y, C_BORDER);
			++y;
		}
		++x;
	}
	minimap->border_overlay = minimap->walls->pixels;
}

void
	draw_scene_background(
		t_scene *scene)
{
	mlx_image_t	*image;
	uint32_t	y;
	uint32_t	x;
	uint32_t	half_height;
	uint32_t	colour;

	image = scene->background;
	half_height = image->height / 2;
	x = 0;
	while (x < image->width)
	{
		y = 0;
		while (y < half_height)
		{
			colour = gradient(y / (float)half_height, scene->ceiling, scene->floor);
			// mlx_put_pixel(image, x, half_height - y, colour);
			mlx_put_pixel(image, x, half_height + y, colour);
			mlx_put_pixel(image, x, half_height - y, scene->ceiling);
			++y;
		}
		++x;
	}
}
