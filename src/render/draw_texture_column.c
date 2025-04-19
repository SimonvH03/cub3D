/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_texture_column.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/27 01:36:33 by simon         #+#    #+#                 */
/*   Updated: 2025/04/19 00:27:03 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	select_texture(
		t_column *column,
		t_walls *walls,
		t_ray *ray)
{
	if (ray->hits_door)
		column->texture = walls->door;
	else if (ray->hit_type == ha_horizontal && ray->sign_y >= 0)
		column->texture = walls->south;
	else if (ray->hit_type == ha_horizontal && ray->sign_y < 0)
		column->texture = walls->north;
	else if (ray->hit_type == ha_vertical && ray->sign_x >= 0)
		column->texture = walls->east;
	else if (ray->hit_type == ha_vertical && ray->sign_x < 0)
		column->texture = walls->west;
}

static void
	vertical_boundaries(
		t_column *column,
		t_ray *ray,
		t_walls *walls,
		t_camera *camera)
{
	column->half_height = walls->image->height / ray->distance / 2;
	column->step = column->texture->height / (float)(column->half_height * 2);
	column->tex_y = 0;
	column->start = walls->image->height - column->half_height
		- camera->height_offset;
	if (column->start < 0)
	{
		column->tex_y = -column->start * column->step;
		column->start = 0;
	}
	column->end = walls->image->height + column->half_height
		- camera->height_offset;
	if ((uint32_t)column->end >= walls->image->height)
		column->end = walls->image->height;
}

// optimized by removing mlx_put_pixel, and storing wall textures column-major
// 0.0005f offset only functions to remove pixel 'jitter' from the center row
//  where otherwise exactly halfway on all textures the y would be consistently
//	miscalculated half of the time because of floating point inaccuracy
// setting higher causes jitter elsewhere, lower doesn't resolve jitter
void
	draw_texture_column(
		t_ray *ray,
		t_walls *walls,
		t_camera *camera,
		uint32_t screen_x)
{
	t_column		column;
	uint32_t		screen_y;
	uint32_t		*texumn_start;

	select_texture(&column, walls, ray);
	vertical_boundaries(&column, ray, walls, camera);
	if (ray->partial >= 1 || ray->partial < 0)
		return ;
	if (((ray->hit_type == ha_vertical && ray->sign_x < 0)
			|| (ray->hit_type == ha_horizontal && ray->sign_y > 0))
		&& !ray->hits_door)
		ray->partial = 1 - ray->partial;
	texumn_start = &((uint32_t *)column.texture->pixels)[column.texture->height
		* (int)(ray->partial * column.texture->width)];
	screen_y = (uint32_t)column.start;
	while (screen_y < (uint32_t)column.end)
	{
		((uint32_t *)walls->image->pixels)[screen_x
			+ screen_y * walls->image->width]
			= texumn_start[(int)(column.tex_y + 0.0005f)];
		column.tex_y += column.step;
		screen_y++;
	}
}
