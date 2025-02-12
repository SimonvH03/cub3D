/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_column_draw.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferid <ferid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:05:56 by svan-hoo          #+#    #+#             */
/*   Updated: 2025/01/22 23:16:13 by ferid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

uint32_t
    get_ray_pixel_colour(
        mlx_texture_t *texture,
        uint32_t tex_x,
        uint32_t tex_y)
{
    uint32_t    index;
    uint8_t     *texel;
    uint32_t    colour;

	if (tex_x >= texture->width || tex_y >= texture->height)
		return (C_TRANSPARENT);
	index = (tex_y * texture->width + tex_x) * texture->bytes_per_pixel;
	texel = &texture->pixels[index];
	colour = texel[0] << 24 | texel[1] << 16 | texel[2] << 8 | texel[3];
	return (colour);
}

static void
	draw_textured_surface(
		t_scene *scene,
		t_column *col,
		t_ray *ray,
		uint32_t screen_x)
{
	uint32_t	tex_x;
	uint32_t	screen_y;
	uint32_t	tex_y;
	uint32_t	colour;

    tex_x = col->x * col->texture->width;
    if ((ray->hit_type == HORIZONTAL && ray->sign_x < 0)
        || (ray->hit_type == VERTICAL && ray->sign_y > 0))
        tex_x = col->texture->width - 1 - tex_x;

    screen_y = (uint32_t)col->start;
    while (screen_y < (uint32_t)col->end)
    {
        tex_y = (int)col->y & (col->texture->height - 1);
        col->y += col->step;
        colour = get_ray_pixel_colour(col->texture, tex_x, tex_y);
        if ((colour & 0xFF) != 0)
            mlx_put_pixel(scene->walls, screen_x, screen_y, colour);
        ++screen_y;
    }
}

static void
	draw_wall(
		t_scene *scene,
		t_ray *ray,
		uint32_t screen_x)
{
	t_column	wall_col;

	ray->pos_x = ray->wall_hit.pos_x;
	ray->pos_y = ray->wall_hit.pos_y;
	ray->distance = ray->wall_hit.distance;
	ray->hit_type = ray->wall_hit.hit_type;
	init_column(scene, ray, &wall_col);
	draw_textured_surface(scene, &wall_col, ray, screen_x);
}

static void
	draw_door(
		t_scene *scene,
		t_ray *ray,
		uint32_t screen_x)
{
	t_column	door_col;

	ray->pos_x = ray->door_hit.pos_x;
	ray->pos_y = ray->door_hit.pos_y;
	ray->distance = ray->door_hit.distance;
	ray->hit_type = ray->door_hit.hit_type;
	init_column(scene, ray, &door_col);
	if (ray->door_hit.door_state
		&& door_col.x < ray->door_hit.door_state->animation_progress)
		return ;
	draw_textured_surface(scene, &door_col, ray, screen_x);
}

void
	draw_texture_column(
		t_scene *scene,
		t_ray *ray,
		uint32_t screen_x)
{
	if (ray->has_wall)
		draw_wall(scene, ray, screen_x);
	if (ray->has_door
		&& (!ray->has_wall || ray->door_hit.distance < ray->wall_hit.distance))
		draw_door(scene, ray, screen_x);
}
