/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_walls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 01:36:33 by simon             #+#    #+#             */
/*   Updated: 2024/09/18 22:11:20 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void
	overlay_border(
		t_minimap *minimap)
{
	uint32_t	pixel_count;
	uint8_t		*src;
	uint8_t		*dst;
	uint32_t	limit;

	pixel_count = 0;
	src = minimap->circle_overlay;
	dst = minimap->walls->pixels;
	limit = minimap->side * minimap->side;
	while (pixel_count < limit)
	{
		if (src[3] % C_TRANSLUCENT == 0)
			dst[3] = src[3];
		++pixel_count;
		src += sizeof(uint32_t);
		dst += sizeof(uint32_t);
	}
}

static uint32_t
	get_minimap_pixel_colour(
		t_minimap *minimap,
		float x,
		float y)
{
	t_scene		*scene;
	t_camera	*camera;
	float		prev_x;

	scene = minimap->r_scene;
	camera = &minimap->r_scene->camera;
	x -= minimap->radius;
	y -= minimap->radius;
	prev_x = x;
	x = prev_x * camera->plane_x + y * -camera->plane_y;
	y = prev_x * camera->plane_y + y * camera->plane_x;
	x /= minimap->block_size;
	y /= minimap->block_size;
	x += camera->pos_x;
	y += camera->pos_y;
	if (x < 0 || x >= scene->x_max
		|| y < 0 || y >= scene->y_max)
		return (C_CEILING);
	if (scene->map[(int)y][(int)x] < 0)
		return (C_CEILING);
	if (scene->map[(int)y][(int)x] > 0)
		return (C_WALL);
	return (C_FLOOR);
}

void
	draw_minimap_walls(
		t_minimap	*minimap)
{
	uint32_t	y;
	uint32_t	x;
	uint32_t	colour;

	y = 0;
	while (y < minimap->walls->height)
	{
		x = 0;
		while (x < minimap->walls->width)
		{
			colour = get_minimap_pixel_colour(minimap, x, y);
			mlx_put_pixel(minimap->walls, x, y, colour);
			++x;
		}
		++y;
	}
	overlay_border(minimap);
}
