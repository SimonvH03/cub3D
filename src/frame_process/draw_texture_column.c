/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture_column.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 01:36:33 by simon             #+#    #+#             */
/*   Updated: 2024/09/23 01:35:19 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// ...else if ((CASE) || 1)... against braindead -Werror=maybe-uninitialized
static void
	init_column(
		t_scene *scene,
		t_ray *ray,
		t_column *column)
{
	t_door_state *door_state = NULL;

	// Check if we hit a door
	if (scene->map[ray->pos_y][ray->pos_x] == TILE_DOOR ||
		scene->map[ray->pos_y][ray->pos_x] == TILE_DOOR_OPEN)
	{
		column->texture = scene->door_texture;
		door_state = get_door_at_position(scene, ray->pos_x, ray->pos_y);
	}
	else
	{
		if (ray->hit_type == HORIZONTAL && ray->sign_x > 0)
			column->texture = scene->east_texture;
		else if (ray->hit_type == HORIZONTAL && ray->sign_x < 0)
			column->texture = scene->west_texture;
		else if (ray->hit_type == VERTICAL && ray->sign_y > 0)
			column->texture = scene->south_texture;
		else if ((ray->hit_type == VERTICAL && ray->sign_y < 0) || 1)
			column->texture = scene->north_texture;
	}
	if (ray->hit_type == HORIZONTAL)
		column->x = scene->camera.pos_y + ray->distance * ray->dir_y;
	else
		column->x = scene->camera.pos_x + ray->distance * ray->dir_x;
	column->x -= (int)column->x;

	// Apply door animation offset if this is a door
	if (door_state)
	{
		// Slide the door texture based on animation progress
		if (ray->hit_type == HORIZONTAL)
		{
			if (ray->sign_x > 0)
				column->x = column->x + door_state->animation_progress;
			else
				column->x = column->x - door_state->animation_progress;
		}
		else
		{
			if (ray->sign_y > 0)
				column->x = column->x + door_state->animation_progress;
			else
				column->x = column->x - door_state->animation_progress;
		}

		// Clamp the texture coordinate
		if (column->x < 0.0f)
			column->x = 0.0f;
		if (column->x > 1.0f)
			column->x = 1.0f;
	}

	column->height = scene->walls->height / ray->distance;
	column->start = (int)(scene->walls->height - column->height) / 2;
	if (column->start < 0)
		column->start = 0;
	column->end = (scene->walls->height + column->height) / 2;
	if ((uint32_t)column->end >= scene->walls->height)
		column->end = scene->walls->height;
	column->step = column->texture->height / (float)column->height;
	column->y = (column->start - (int)scene->walls->height / 2
			+ column->height / 2) * column->step;
}

static uint32_t
	get_ray_pixel_colour(
		mlx_texture_t *texture,
		uint32_t tex_x,
		uint32_t tex_y)
{
	uint32_t	colour;
	uint32_t	index;
	uint8_t		*texel;

	// Check bounds first
	if (tex_x >= texture->width || tex_y >= texture->height)
		return (C_TRANSPARENT);

	// Calculate byte index
	index = (tex_y * texture->width + tex_x) * texture->bytes_per_pixel;
	texel = &texture->pixels[index];
	colour = texel[0] << 24 | texel[1] << 16 | texel[2] << 8 | texel[3];
	return (colour);
}

void
	draw_texture_column(
		t_scene *scene,
		t_ray *ray,
		uint32_t screen_x)
{
	t_column		column;
	uint32_t		tex_x;
	uint32_t		screen_y;
	uint32_t		tex_y;
	uint32_t		colour;

	init_column(scene, ray, &column);
	tex_x = column.x * column.texture->width;
	if ((ray->hit_type == HORIZONTAL && ray->sign_x < 0)
		|| (ray->hit_type == VERTICAL && ray->sign_y > 0))
		tex_x = column.texture->width - 1 - tex_x;
	screen_y = (uint32_t)column.start;
	while (screen_y < (uint32_t)column.end)
	{
		tex_y = (int)column.y & (column.texture->height - 1);
		column.y += column.step;
		colour = get_ray_pixel_colour(column.texture, tex_x, tex_y);
		mlx_put_pixel(scene->walls, screen_x, screen_y, colour);
		++screen_y;
	}
}
