/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 01:36:33 by simon             #+#    #+#             */
/*   Updated: 2024/08/27 15:59:58 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void
	init_ray(
		t_ray *ray,
		float camera_x,
		t_camera camera)
{
	ray->dir_y = camera.dir_y + camera.plane_y * camera_x;
	ray->dir_x = camera.dir_x + camera.plane_x * camera_x;
	ray->step_y = ft_abs_float(1 / ray->dir_y);
	ray->step_x = ft_abs_float(1 / ray->dir_x);
	ray->sign_y = ft_sign_float(ray->dir_y);
	ray->sign_x = ft_sign_float(ray->dir_x);
	ray->pos_y = (int)camera.pos_y;
	ray->pos_x = (int)camera.pos_x;
	if (ray->sign_y > 0)
		ray->total_y = ((ray->pos_y + 1) - camera.pos_y * ray->step_y);
	else
		ray->total_y = (camera.pos_y - ray->pos_y) * ray->step_y;
	if (ray->sign_x > 0)
		ray->total_x = ((ray->pos_x + 1) - camera.pos_x * ray->step_x);
	else
		ray->total_x = (camera.pos_x - ray->pos_x) * ray->step_x;
}

// assuming the camera is not inside a wall;
//	shift map position to the nearest (total_y <> total_x) grid line;
//	and check wall type (0 or positive int 1-N)
static int
	cast_ray(
		t_ray *ray,
		t_scene *scene)
{
	int	wall_type;

	wall_type = 0;
	while (wall_type == 0
		&& ray->pos_y && ray->pos_x
		&& ray->pos_y < scene->y_max && ray->pos_x < scene->x_max)
	{
		if (ray->total_y > ray->total_x)
		{
			
		}
		wall_type = scene->map[ray->pos_y][ray->pos_x];
	}
	return (wall_type);
}

void
	raycast(
		void *param)
{
	t_cub3d		*cub3d;
	uint32_t	screen_x;
	t_ray		ray;
	float		camera_x;

	cub3d = param;
	screen_x = 0;
	while (screen_x < cub3d->image->width)
	{
		camera_x = 2 * screen_x / (float)cub3d->image->width - 1;
		intit_ray(&ray, camera_x, cub3d->scene->camera);
		cast_ray(&ray, cub3d->scene);
		++screen_x;
	}
}
