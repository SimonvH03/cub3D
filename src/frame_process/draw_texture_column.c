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
	// Draw wall first if it's visible
	if (ray->has_wall)
	{
		t_column wall_col;
		ray->pos_x = ray->wall_hit.pos_x;
		ray->pos_y = ray->wall_hit.pos_y;
		ray->distance = ray->wall_hit.distance;
		ray->hit_type = ray->wall_hit.hit_type;
		init_column(scene, ray, &wall_col);

		uint32_t tex_x = wall_col.x * wall_col.texture->width;
		if ((ray->hit_type == HORIZONTAL && ray->sign_x < 0)
			|| (ray->hit_type == VERTICAL && ray->sign_y > 0))
			tex_x = wall_col.texture->width - 1 - tex_x;

		uint32_t screen_y = (uint32_t)wall_col.start;
		while (screen_y < (uint32_t)wall_col.end)
		{
			uint32_t tex_y = (int)wall_col.y & (wall_col.texture->height - 1);
			wall_col.y += wall_col.step;
			uint32_t colour = get_ray_pixel_colour(wall_col.texture, tex_x, tex_y);
			if ((colour & 0xFF000000) != 0)
				mlx_put_pixel(scene->walls, screen_x, screen_y, colour);
			++screen_y;
		}
	}

	// Draw door if it's closer than the wall
	if (ray->has_door && (!ray->has_wall || ray->door_hit.distance < ray->wall_hit.distance))
	{
		t_column door_col;
		ray->pos_x = ray->door_hit.pos_x;
		ray->pos_y = ray->door_hit.pos_y;
		ray->distance = ray->door_hit.distance;
		ray->hit_type = ray->door_hit.hit_type;
		init_column(scene, ray, &door_col);

		// Skip drawing if we're in the open part of the door
		if (ray->door_hit.door_state && door_col.x < ray->door_hit.door_state->animation_progress)
			return;

		uint32_t tex_x = door_col.x * door_col.texture->width;
		if ((ray->hit_type == HORIZONTAL && ray->sign_x < 0)
			|| (ray->hit_type == VERTICAL && ray->sign_y > 0))
			tex_x = door_col.texture->width - 1 - tex_x;

		uint32_t screen_y = (uint32_t)door_col.start;
		while (screen_y < (uint32_t)door_col.end)
		{
			uint32_t tex_y = (int)door_col.y & (door_col.texture->height - 1);
			door_col.y += door_col.step;
			uint32_t colour = get_ray_pixel_colour(door_col.texture, tex_x, tex_y);
			if ((colour & 0xFF000000) != 0)
				mlx_put_pixel(scene->walls, screen_x, screen_y, colour);
			++screen_y;
		}
	}
}
