/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_interaction.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/09 19:05:56 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/04/19 23:02:23 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	init_interaction_ray(
		t_interaction_ray *ray,
		t_camera *camera)
{
	ray->pos_x = (int)camera->pos_x;
	ray->pos_y = (int)camera->pos_y;
	ray->dir_x = camera->dir_x;
	ray->dir_y = camera->dir_y;
	ray->sign_x = ft_sign_float(ray->dir_x);
	ray->sign_y = ft_sign_float(ray->dir_y);
	ray->step_x = ft_abs_float(1 / ray->dir_x);
	if (ray->step_x == INFINITY)
		ray->step_x = (float)UINT32_MAX;
	ray->step_y = ft_abs_float(1 / ray->dir_y);
	if (ray->step_y == INFINITY)
		ray->step_y = (float)UINT32_MAX;
	if (ray->sign_x > 0)
		ray->total_x = ((ray->pos_x + 1 - camera->pos_x) * ray->step_x);
	else
		ray->total_x = (camera->pos_x - ray->pos_x) * ray->step_x;
	if (ray->sign_y > 0)
		ray->total_y = ((ray->pos_y + 1 - camera->pos_y) * ray->step_y);
	else
		ray->total_y = (camera->pos_y - ray->pos_y) * ray->step_y;
}

static int
	cast_interaction_ray(
		t_interaction_ray *ray,
		t_grid *grid)
{
	int		cell;

	while (true)
	{
		if (ray->total_x < ray->total_y)
		{
			ray->total_x += ray->step_x;
			ray->pos_x += ray->sign_x;
			ray->distance = ray->total_x - ray->step_x;
		}
		else
		{
			ray->total_y += ray->step_y;
			ray->pos_y += ray->sign_y;
			ray->distance = ray->total_y - ray->step_y;
		}
		cell = grid->tilemap[ray->pos_y][ray->pos_x];
		if (is_solid(cell) || is_door(cell))
		{
			if (ray->distance > INTERACTION_RANGE)
				return (-1);
			return (cell);
		}
	}
	return (-1);
}

void
	player_interaction(
		t_grid *grid,
		t_camera *camera)
{
	int					cell;
	t_interaction_ray	ray;

	init_interaction_ray(&ray, camera);
	cell = cast_interaction_ray(&ray, grid);
	if (is_door(cell))
	{
		operate_door(&grid->door_list[get_id(cell)], camera);
	}
}
