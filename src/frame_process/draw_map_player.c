/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 01:36:33 by simon             #+#    #+#             */
/*   Updated: 2024/09/18 22:14:43 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static uint32_t
	get_player_pixel_colour(
		t_map *map,
		float x,
		float y)
{
	t_camera		*camera;
	mlx_texture_t	*texture;
	float			prev_x;
	uint32_t		index;
	uint8_t			*pixelstart;

	texture = map->r_scene->player_texture;
	camera = &map->r_scene->camera;
	x -= map->player->width / (float)2;
	y -= map->player->height / (float)2;
	prev_x = x;
	x = prev_x * camera->plane_x + y * camera->plane_y;
	y = prev_x * -camera->plane_y + y * camera->plane_x;
	x *= sqrtf(2);
	y *= sqrtf(2);
	x += texture->width / (float)2;
	y += texture->height / (float)2;
	if (x < 0 || x >= texture->width
		|| y < 0 || y >= texture->height)
		return (0x00000000);
	index = ((int)y * texture->width + (int)x) * sizeof(uint32_t);
	pixelstart = &texture->pixels[index];
	return ((uint32_t)(pixelstart[0] << 24 | pixelstart[1] << 16
		| pixelstart[2] << 8 | pixelstart[3]));
}

void
	draw_map_player(
		t_map *map)
{
	uint32_t	y;
	uint32_t	x;
	uint32_t	colour;

	y = 0;
	while (y < map->player->height)
	{
		x = 0;
		while (x < map->player->width)
		{
			colour = get_player_pixel_colour(map, x, y);
			mlx_put_pixel(map->player, x, y, colour);
			++x;
		}
		++y;
	}
	map->player->instances[0].x = map->x_offset;
	map->player->instances[0].y = map->y_offset;
	map->player->instances[0].x += map->r_scene->camera.pos_x * map->block_size;
	map->player->instances[0].y += map->r_scene->camera.pos_y * map->block_size;
}
