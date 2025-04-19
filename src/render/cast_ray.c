/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_ray.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <simon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/24 02:16:25 by simon         #+#    #+#                 */
/*   Updated: 2025/04/15 22:08:51 by svan-hoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int16_t
	see_through(
		t_grid *grid,
		t_ray *ray,
		float cell_shift)
{
	int			steps;
	int			i;

	steps = ft_abs((int)cell_shift) + (cell_shift < 0);
	i = 1;
	if (ray->hit_type == ha_horizontal)
	{
		while (i <= steps)
			if (ray->pos_y + i * ray->sign_x >= grid->x_max
				|| (int32_t)ray->pos_y + i * ray->sign_x < 0
				|| !is_door(grid->tilemap
					[ray->pos_y][ray->pos_x + ray->sign_x * i++]))
				return (RETURN_FAILURE);
		return (grid->tilemap[ray->pos_y][ray->pos_x + ray->sign_x * steps]);
	}
	else
	{
		while (i <= steps)
			if (ray->pos_x + i * ray->sign_y >= grid->y_max
				|| (int32_t)ray->pos_x + i * ray->sign_y < 0
				|| !is_door(grid->tilemap
					[ray->pos_y + ray->sign_y * i++][ray->pos_x]))
				return (RETURN_FAILURE);
		return (grid->tilemap[ray->pos_y + ray->sign_y * steps][ray->pos_x]);
	}
}

static void
	door_half_step(
		t_ray *ray,
		t_grid *grid,
		int16_t	cell)
{
	float		cell_shift;

	if (ray->hit_type == ha_horizontal)
		cell_shift = ray->partial + (ray->step_y * 0.5) * ray->dir_x;
	else
		cell_shift = ray->partial + (ray->step_x * 0.5) * ray->dir_y;
	if (cell_shift < 0 || cell_shift > 1)
	{
		cell = see_through(grid, ray, cell_shift);
		if (cell == RETURN_FAILURE)
			return ;
	}
	ray->partial = (cell_shift - (int)cell_shift) + (cell_shift < 0);
	ray->door_position = grid->door_list[get_id(cell)].position;
	if (get_type(cell) == 'd')
		ray->partial = 1 - ray->partial;
	ray->hits_door = (ray->partial < ray->door_position);
	if (ray->hits_door)
	{
		ray->partial += 1 - ray->door_position;
		ray->total_y += ray->step_y * 0.5;
		ray->total_x += ray->step_x * 0.5;
	}
}

static void
	calculate_partial(
		t_ray *ray)
{
	if (ray->hit_type == ha_vertical)
		ray->partial = ray->start_y
			+ (ray->total_x - ray->step_x) * ray->dir_y;
	else
		ray->partial = ray->start_x
			+ (ray->total_y - ray->step_y) * ray->dir_x;
	ray->partial -= (int)ray->partial;
}

static bool
	hit_position(
		t_ray *ray,
		t_grid *grid,
		int pos_y,
		int pos_x)
{
	const int16_t	cell = grid->tilemap[pos_y][pos_x];
	int16_t			facing_cell;

	if (is_solid(cell) == false && !is_door(cell))
		return (false);
	calculate_partial(ray);
	if (ft_isdigit(get_type(cell)))
		return (true);
	if (is_door(cell))
	{
		if (ray->hit_type == ha_horizontal)
			facing_cell = grid->tilemap[pos_y - ray->sign_y][pos_x];
		else
			facing_cell = grid->tilemap[pos_y][pos_x - ray->sign_x];
		if (is_door(facing_cell))
			return (false);
	}
	if (is_door(cell))
	{
		calculate_partial(ray);
		door_half_step(ray, grid, cell);
		return (ray->hits_door);
	}
	return (true);
}

// assuming the camera is not inside a wall;
//	shift map position to the nearest (total_y <> total_x) grid line;
//	and check wall type (' ', 0-9)
void
	cast_ray(
		t_ray *ray,
		t_grid *grid)
{
	while (true)
	{
		if (ray->total_y < ray->total_x)
		{
			ray->total_y += ray->step_y;
			ray->pos_y += ray->sign_y;
			ray->hit_type = ha_horizontal;
		}
		else
		{
			ray->total_x += ray->step_x;
			ray->pos_x += ray->sign_x;
			ray->hit_type = ha_vertical;
		}
		if (hit_position(ray, grid, ray->pos_y, ray->pos_x) == true)
			break ;
	}
	if (ray->hit_type == ha_horizontal)
		ray->distance = ray->total_y - ray->step_y;
	else
		ray->distance = ray->total_x - ray->step_x;
}
