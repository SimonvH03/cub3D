/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_draw_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 01:36:33 by simon             #+#    #+#             */
/*   Updated: 2024/08/30 05:36:15 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void
	overlay_border(
		t_minimap *minimap)
{
	uint32_t	pixel_count;
	uint32_t	colour;
	uint8_t		*p;
	uint32_t	y;
	uint32_t	x;

	y = 0;
	while (y < minimap->walls->height)
	{
		x = 0;
		while (x < minimap->walls->width)
		{
			p = (uint8_t *)&colour;
			*(p++) = (uint8_t)(minimap->overlay[pixel_count] >> 24);
			*(p++) = (uint8_t)(minimap->overlay[pixel_count] >> 16);
			*(p++) = (uint8_t)(minimap->overlay[pixel_count] >> 8);
			*(p++) = (uint8_t)(minimap->overlay[pixel_count] & 0xFF);
			if (colour != 0x00000000)
				mlx_put_pixel(minimap->walls, x, y, colour);
			++x;
			++pixel_count;
		}
		++y;
	}
}

static uint32_t
	transform_minimap_pixel(
		t_minimap *minimap,
		float x,
		float y)
{
	float		scale = minimap->side / minimap->scene->y_max;

	x /= scale;
	y /= scale;
	x += minimap->scene->camera.pos_x - minimap->scene->y_max / (float)2;
	y += minimap->scene->camera.pos_y - minimap->scene->y_max / (float)2;
	if (x < 0 || x >= minimap->scene->x_max
		|| y < 0 || y >= minimap->scene->y_max)
		return (C_CEILING);
	if (minimap->scene->map[(int)y][(int)x] < 0)
		return (C_CEILING);
	if (minimap->scene->map[(int)y][(int)x] > 0)
		return (C_WALL);
	return (C_FLOOR);
}

void
	draw_minimap(
		void *param)
{
	t_minimap	*minimap;
	uint32_t	y;
	uint32_t	x;
	uint32_t	colour;

	minimap = param;
	y = minimap->inner_side;
	while (y < minimap->side - minimap->inner_side)
	{
		x = minimap->inner_side;
		while (x < minimap->side - minimap->inner_side)
		{
			// if (is_in_circle(minimap->c_offset, minimap->c_offset,
			// 	minimap->radius, x, y) == true)
			// {
				colour = transform_minimap_pixel(minimap, x, y);
				mlx_put_pixel(minimap->walls, x, y, colour);
			// }
			++x;
		}
		++y;
	}
	overlay_border(minimap);
	mlx_put_pixel(minimap->walls, minimap->side / 2, minimap->side / 2, 0x00FF00FF);
}
