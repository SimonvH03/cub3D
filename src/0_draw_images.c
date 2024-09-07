/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_draw_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/09/07 04:00:55 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void
	draw_minimap_circle_overlay(
		t_minimap *minimap)
{
	uint32_t	y;
	uint32_t	x;

	x = 0;
	while (x < minimap->side)
	{
		y = 0;
		while (y < minimap->side)
		{
			if (is_in_circle(x - (float)minimap->c_offset,
					y - (float)minimap->c_offset,
					minimap->radius) == false)
				mlx_put_pixel(minimap->walls, x, y, C_TRANSPARENT);
			else if (is_in_circle(x - (float)minimap->c_offset,
					y - (float)minimap->c_offset,
					minimap->radius * 15 / 16) == false)
				mlx_put_pixel(minimap->walls, x, y, C_BORDER);
			else
				mlx_put_pixel(minimap->walls, x, y, C_WALL);
			++y;
		}
		++x;
	}
	ft_memcpy(minimap->circle_overlay, minimap->walls->pixels,
		minimap->walls->width * minimap->walls->height * sizeof(uint32_t));
}

void
	draw_scene_background(
		t_scene *scene)
{
	uint32_t	y;
	uint32_t	x;

	x = 0;
	while (x < scene->background->width)
	{
		y = 0;
		while (y < scene->background->height / 2)
		{
			mlx_put_pixel(scene->background, x, y, scene->ceiling);
			++y;
		}
		while (y < scene->background->height)
		{
			mlx_put_pixel(scene->background, x, y, scene->floor);
			++y;
		}
		++x;
	}
}
