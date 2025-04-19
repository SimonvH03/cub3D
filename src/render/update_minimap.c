/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_minimap.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/22 19:48:15 by simon         #+#    #+#                 */
/*   Updated: 2025/04/19 00:38:24 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t
	minimap_sampled_colour(
		t_grid *grid,
		float x,
		float y)
{
	const int16_t	cell = grid->tilemap[(int)y][(int)x];
	float			partial;

	if (get_type(cell) == ' ')
		return (C_CEILING);
	else if (is_door(cell))
	{
		if (get_axis(cell))
			partial = x - (int)x;
		else
			partial = y - (int)y;
		if (get_type(cell) == 'd')
			partial = 1 - partial;
		if (partial > grid->door_list[get_id(cell)].position)
			return (C_OPENDOOR);
		return (C_DOOR);
	}
	else if (is_solid(cell))
		return (C_WALL);
	else
		return (C_FLOOR);
}

static void
	sample_wall(
		mlx_image_t *walls,
		uint32_t img_x,
		uint32_t img_y,
		void *param)
{
	const t_minimap		*minimap = param;
	const t_camera		*camera = minimap->r_camera;
	float				prev_x;
	float				x;
	float				y;

	x = img_x;
	x -= minimap->radius;
	y = img_y;
	y -= minimap->radius;
	prev_x = x;
	x = prev_x * -camera->dir_y + y * -camera->dir_x;
	y = prev_x * camera->dir_x + y * -camera->dir_y;
	x = x / minimap->block_size + camera->pos_x;
	y = y / minimap->block_size + camera->pos_y;
	if (x < 0 || x >= minimap->r_grid->x_max
		|| y < 0 || y >= minimap->r_grid->y_max)
		((uint32_t *)walls->pixels)[img_y * walls->width + img_x] = C_CEILING;
	else
		((uint32_t *)walls->pixels)[img_y * walls->width + img_x]
			= minimap_sampled_colour(minimap->r_grid, x, y);
}

static void
	overlay_border(
		t_minimap *minimap)
{
	uint32_t		pixel_count;
	const uint32_t	limit = minimap->side * minimap->side;
	uint8_t			*src;
	uint8_t			*dst;

	src = minimap->circle_overlay;
	dst = minimap->walls->pixels;
	pixel_count = 0;
	while (pixel_count < limit)
	{
		if (src[3] % 0x42 == 0)
			dst[3] = src[3];
		++pixel_count;
		src += sizeof(uint32_t);
		dst += sizeof(uint32_t);
	}
}

void
	update_minimap(
		t_minimap	*minimap)
{
	if (get_minimap_ability(minimap) == false)
		return ;
	image_iter(minimap->walls, sample_wall, minimap);
	overlay_border(minimap);
}
