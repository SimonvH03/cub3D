/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 01:36:33 by simon             #+#    #+#             */
/*   Updated: 2024/08/27 19:52:39 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void
	init_ray(
		t_ray *ray,
		double camera_x,
		t_camera *camera)
{
	ray->pos_y = (int)camera->pos_y;
	ray->pos_x = (int)camera->pos_x;
	ray->dir_y = camera->dir_y + camera->plane_y * camera_x;
	ray->dir_x = camera->dir_x + camera->plane_x * camera_x;
	if (ray->dir_y == 0)
		ray->step_y = HEIGHT;
	else
		ray->step_y = ft_abs_double(1 / ray->dir_y);
	if (ray->dir_x == 0)
		ray->step_x = WIDTH;
	else
		ray->step_x = ft_abs_double(1 / ray->dir_x);
	ray->sign_y = ft_sign_double(ray->dir_y);
	ray->sign_x = ft_sign_double(ray->dir_x);
	if (ray->sign_y > 0)
		ray->total_y = ((ray->pos_y + 1) - camera->pos_y * ray->step_y);
	else
		ray->total_y = (camera->pos_y - ray->pos_y) * ray->step_y;
	if (ray->sign_x > 0)
		ray->total_x = ((ray->pos_x + 1) - camera->pos_x * ray->step_x);
	else
		ray->total_x = (camera->pos_x - ray->pos_x) * ray->step_x;
	print_ray(ray);
}

// assuming the camera is not inside a wall;
//	shift map position to the nearest (total_y <> total_x) grid line;
//	and check wall type (0 or positive int 1-N)
static double
	cast_ray(
		t_ray *ray,
		t_scene *scene)
{
	short	axis;

	while (ray->pos_x && ray->pos_x < scene->x_max
		&& ray->pos_y && ray->pos_y < scene->y_max)// true crashes if casting skips walls or map is not enclosed in walls
	{
		if (ray->total_y < ray->total_x)
		{
			printf("\e[32mrty %-10f < rtx %-10f\e[0m\n", ray->total_y, ray->total_x);
			ray->total_y += ray->step_y;
			ray->pos_y += ray->sign_y;
			axis = 0;
		}
		else
		{
			printf("\e[32mrtx %-10f < rty %-10f\e[0m\n", ray->total_x, ray->total_y);
			ray->total_x += ray->step_x;
			ray->pos_x += ray->sign_x;
			axis = 1;
		}
		if (scene->map[ray->pos_y][ray->pos_x])
			break ;
	}
	if (axis == 0)
		return (ray->total_y - ray->step_y);
	else
		return (ray->total_x - ray->step_x);
}

void
	draw_ray(
		mlx_image_t *image,
		uint32_t screen_x,
		float distance)
{
	uint32_t	height;
	uint32_t	y;

	height = image->height / distance;
	if (height > image->height)
		height = image->height;
	y = 0;
	while (y < height / 2)
	{
		mlx_put_pixel((mlx_image_t *)image, screen_x, height / 2 + y, 0xFF00FFFF);
		mlx_put_pixel((mlx_image_t *)image, screen_x, height / 2 - y, 0xFF00FFFF);
		++y;
		usleep(1000);
	}
}

void
	raycast(
		void *param)
{
	t_cub3d		*cub3d;
	uint32_t	screen_x;
	t_ray		ray;
	double		camera_x;
	double		distance;

	cub3d = param;
	usleep(1000);
	draw_background(cub3d->image, cub3d->scene);
	screen_x = 0;
	while (screen_x <= cub3d->image->width)
	{
		camera_x = 2 * screen_x / (double)cub3d->image->width - 1;
		init_ray(&ray, camera_x, cub3d->scene->camera);
		distance = cast_ray(&ray, cub3d->scene);
		printf("\e[33mSCREEN_X %d\e[0m\ncamera_x %d/%d\ndistance %f\n\n", screen_x, (int)(camera_x * WIDTH), WIDTH, distance);
		draw_ray(cub3d->image, screen_x, distance);
		++screen_x;
	}
}
