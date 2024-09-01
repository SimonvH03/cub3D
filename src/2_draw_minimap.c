/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_draw_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 01:36:33 by simon             #+#    #+#             */
/*   Updated: 2024/09/01 14:41:39 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void
	overlay_border(
		t_minimap *minimap)
{
	uint32_t	pixel_count;
	uint8_t		*src;
	uint8_t		*dst;
	uint32_t	limit;

	pixel_count = 0;
	src = minimap->overlay;
	dst = minimap->walls->pixels;
	limit = minimap->side * minimap->side;
	while (pixel_count < limit)
	{
		if (src[3] % C_BORDER >> 24 == 0)
			dst[3] = src[3];
		++pixel_count;
		src += sizeof(uint32_t);
		dst += sizeof(uint32_t);
	}
}

// static uint32_t
// 	transform_minimap_pixel(
// 		t_minimap *minimap,
// 		float x,
// 		float y)
// {
// 	float		scale = minimap->side / minimap->scene->y_max;

// 	x /= scale;
// 	y /= scale;
// 	x += minimap->scene->camera.pos_x - minimap->scene->y_max / (float)2;
// 	y += minimap->scene->camera.pos_y - minimap->scene->y_max / (float)2;
// 	if (x < 0 || x >= minimap->scene->x_max
// 		|| y < 0 || y >= minimap->scene->y_max)
// 		return (C_CEILING);
// 	if (minimap->scene->map[(int)y][(int)x] < 0)
// 		return (C_CEILING);
// 	if (minimap->scene->map[(int)y][(int)x] > 0)
// 		return (C_WALL);
// 	return (C_FLOOR);
// }

static uint32_t
	transform_minimap_pixel(
		t_minimap *minimap,
		float x,
		float y)
{
	t_scene		*scene;
	t_camera	*camera;
	float		prev_x;

	scene = minimap->scene;
	camera = &minimap->scene->camera;
	x -= minimap->c_offset;
	y -= minimap->c_offset;
	prev_x = x;
	x = prev_x * camera->plane_x + y * -camera->plane_y;
	y = prev_x * camera->plane_y + y * camera->plane_x;
	x /= MINIMAP_SCALE;
	y /= MINIMAP_SCALE;
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
	draw_minimap(
		void *param)
{
	t_minimap	*minimap;
	uint32_t	y;
	uint32_t	x;
	uint32_t	colour;

	minimap = param;
	if (minimap->scene->recast == false)
		return ;
	y = minimap->inner_side;
	while (y < minimap->side - minimap->inner_side)
	{
		x = minimap->inner_side;
		while (x < minimap->side - minimap->inner_side)
		{
			colour = transform_minimap_pixel(minimap, x, y);
			mlx_put_pixel(minimap->walls, x, y, colour);
			++x;
		}
		++y;
	}
	overlay_border(minimap);
	mlx_put_pixel(minimap->walls, minimap->side / 2, minimap->side / 2, 0x00FF00FF);
	// minimap->scene->recast = false;
}
