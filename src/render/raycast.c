/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/24 02:16:25 by simon         #+#    #+#                 */
/*   Updated: 2025/04/21 21:55:51 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	draw_background(
		t_scene *scene,
		t_camera *camera)
{
	mlx_image_t	*image;
	uint32_t	x;
	uint32_t	y;

	image = scene->walls.image;
	y = 0;
	while (y < image->height - camera->height_offset)
	{
		x = 0;
		while (x < image->width)
			((uint32_t *)image->pixels)[x++ + y * image->width]
				= scene->ceiling_clr;
		y++;
	}
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
			((uint32_t *)image->pixels)[x++ + y * image->width]
				= scene->floor_clr;
		y++;
	}
}

static void
	init_ray(
		t_ray *ray,
		t_camera *camera)
{
	ray->pos_x = (int)camera->pos_x;
	ray->pos_y = (int)camera->pos_y;
	ray->dir_x = camera->dir_x + camera->plane_x * ray->camera_x;
	ray->dir_y = camera->dir_y + camera->plane_y * ray->camera_x;
	ray->step_x = ft_abs_float(1 / ray->dir_x);
	if (ray->step_x == INFINITY)
		ray->step_x = (float)UINT32_MAX;
	ray->step_y = ft_abs_float(1 / ray->dir_y);
	if (ray->step_y == INFINITY)
		ray->step_y = (float)UINT32_MAX;
	ray->sign_x = ft_sign_float(ray->dir_x);
	ray->sign_y = ft_sign_float(ray->dir_y);
	if (ray->sign_x > 0)
		ray->total_x = ((ray->pos_x + 1 - camera->pos_x) * ray->step_x);
	else
		ray->total_x = (camera->pos_x - ray->pos_x) * ray->step_x;
	if (ray->sign_y > 0)
		ray->total_y = ((ray->pos_y + 1 - camera->pos_y) * ray->step_y);
	else
		ray->total_y = (camera->pos_y - ray->pos_y) * ray->step_y;
	ray->start_x = camera->pos_x;
	ray->start_y = camera->pos_y;
	ray->distance = 0;
}

void
	raycast(
		t_scene *scene,
		t_camera *camera)
{
	t_ray		ray;
	uint32_t	x;

	draw_background(scene, camera);
	x = 0;
	while (x < scene->walls.image->width)
	{
		ray.camera_x = x / (float)(scene->walls.image->width - 1) - 0.5;
		init_ray(&ray, camera);
		cast_ray(&ray, &scene->grid);
		draw_texture_column(&ray, &scene->walls, camera, x);
		++x;
	}
}
