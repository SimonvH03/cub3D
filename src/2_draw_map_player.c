/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_draw_map_player.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 01:36:33 by simon             #+#    #+#             */
/*   Updated: 2024/09/08 03:55:49 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void
	toggle_maps(
		t_minimap *minimap,
		t_map *map)
{
	minimap->player->enabled = !minimap->player->enabled;
	minimap->walls->enabled = !minimap->walls->enabled;
	minimap->enabled = !minimap->enabled;
	map->player->enabled = !map->player->enabled;
	map->walls->enabled = !map->walls->enabled;
	map->enabled = !map->enabled;
}

static uint32_t
	transform_player_pixel(
		t_map *map,
		float x,
		float y)
{
	t_scene		*scene;
	t_camera	*camera;
	float		prev_x;
	int			pixel_index;
	uint8_t		*pixelstart;

	scene = map->scene;
	camera = &map->scene->camera;

	x -= map->player->width / (float)2;
	y -= map->player->height / (float)2;

	prev_x = x;
	x = prev_x * camera->plane_x + y * -camera->plane_y;
	y = prev_x * camera->plane_y + y * camera->plane_x;

	x += map->player->width / (float)2;
	y += map->player->height / (float)2;

	if (x > scene->player_texture->width || y > scene->player_texture->height)
		return (0x00);
	pixel_index = (y * scene->player_texture->width + x) * scene->player_texture->bytes_per_pixel;
	pixelstart = &scene->player_texture->pixels[pixel_index];
	return ((uint32_t)(pixelstart[0] << 24 | pixelstart[1] << 16 | pixelstart[2] << 8 | pixelstart[3]));
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
			colour = transform_player_pixel(map, x, y);
			mlx_put_pixel(map->player, x, y, colour);
			++x;
		}
		++y;
	}
}