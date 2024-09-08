/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_draw_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/09/08 02:59:53 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

// for illustrative purposes, set outer circle pixel colour to C_TRANSLUCENT
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
			if (is_in_circle(x - (float)minimap->radius,
					y - (float)minimap->radius,
					minimap->radius) == false)
				mlx_put_pixel(minimap->walls, x, y, C_TRANSPARENT);
			else if (is_in_circle(x - (float)minimap->radius,
					y - (float)minimap->radius,
					minimap->radius * 39 / 42) == false)
				mlx_put_pixel(minimap->walls, x, y, C_TRANSLUCENT);
			else
				mlx_put_pixel(minimap->walls, x, y, C_WALL);
			++y;
		}
		++x;
	}
	ft_memcpy(minimap->circle_overlay, minimap->walls->pixels,
		minimap->walls->width * minimap->walls->height * sizeof(uint32_t));
}

static uint32_t
	transform_map_pixel(
		t_map *map,
		float x,
		float y,
		float map_scale)
{
	t_scene		*scene;

	scene = map->scene;
	x -= map->walls->width / 2;
	y -= map->walls->height / 2;
	x *= map_scale;
	y *= map_scale;
	x += scene->x_max / 2;
	y += scene->y_max / 2;
	if (x < 0 || x >= scene->x_max
		|| y < 0 || y >= scene->y_max)
		return (C_TRANSLUCENT);
	if (scene->map[(int)y][(int)x] < 0)
		return (C_TRANSLUCENT);
	if (scene->map[(int)y][(int)x] > 0)
		return (C_WALL);
	return (C_FLOOR);
}

void
	draw_map_walls(
		t_map *map)
{
	uint32_t	y;
	uint32_t	x;
	uint32_t	colour;
	float		map_scale;

	if (map->scene->y_max > map->scene->x_max)
		map_scale = (map->scene->y_max + 2) / (float)map->walls->height;
	else
		map_scale = (map->scene->x_max + 2) / (float)map->walls->width;
	y = 0;
	while (y < map->walls->height)
	{
		x = 0;
		while (x < map->walls->width)
		{
			colour = transform_map_pixel(map, x, y, map_scale);
			mlx_put_pixel(map->walls, x, y, colour);
			++x;
		}
		++y;
	}
	
}
