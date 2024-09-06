/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_draw_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 01:36:33 by simon             #+#    #+#             */
/*   Updated: 2024/09/05 18:23:07 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void
	init_ray(
		t_ray *ray,
		t_camera *camera)
{
	ray->pos_y = (int)camera->pos_y;
	ray->pos_x = (int)camera->pos_x;
	ray->dir_y = camera->dir_y + camera->plane_y * ray->camera_x;
	ray->dir_x = camera->dir_x + camera->plane_x * ray->camera_x;
	ray->step_y = ft_abs_float(1 / ray->dir_y);
	ray->step_x = ft_abs_float(1 / ray->dir_x);
	ray->sign_y = ft_sign_float(ray->dir_y);
	ray->sign_x = ft_sign_float(ray->dir_x);
	if (ray->sign_y > 0)
		ray->total_y = ((ray->pos_y + 1 - camera->pos_y) * ray->step_y);
	else
		ray->total_y = (camera->pos_y - ray->pos_y) * ray->step_y;
	if (ray->sign_x > 0)
		ray->total_x = ((ray->pos_x + 1 - camera->pos_x) * ray->step_x);
	else
		ray->total_x = (camera->pos_x - ray->pos_x) * ray->step_x;
	ray->distance = 0;
}

// assuming the camera is not inside a wall;
//	shift map position to the nearest (total_y <> total_x) grid line;
//	and check wall type (0 or positive int 1-N)
static void
	cast_ray(
		t_ray *ray,
		t_scene *scene)
{
	// while (true)// crashes if casting skips walls or camera is not enclosed in walls
	while (ray->pos_x && ray->pos_x < scene->x_max
		&& ray->pos_y && ray->pos_y < scene->y_max)
	{
		if (ray->total_y < ray->total_x)
		{
			ray->total_y += ray->step_y;
			ray->pos_y += ray->sign_y;
		}
		else
		{
			ray->total_x += ray->step_x;
			ray->pos_x += ray->sign_x;
		}
		if (scene->map[ray->pos_y][ray->pos_x] > 0)
			break ;
	}
	if (ray->step_y == INFINITY)
		ray->distance = ray->total_x - ray->step_x;
	else if (ray->step_x == INFINITY)
		ray->distance = ray->total_y - ray->step_y;
	else
		ray->distance = ft_max_float(ray->total_y - ray->step_y,
			ray->total_x - ray->step_x);
	ray->distance = ft_max_float(ray->distance, 1);
}

void
	draw_ray(
		mlx_image_t *image,
		uint32_t screen_x,
		uint32_t wall_height)
{
	uint8_t		*pixelstart;
	uint8_t		*pixelend;

	pixelstart = &image->pixels[((image->height / 2 - wall_height)* image->width + screen_x) * sizeof(uint32_t)];
	// pixelend = &image->pixels[((image->height / 2 + wall_height) * image->width + screen_x) * sizeof(uint32_t)];
	pixelend = pixelstart + 2 * wall_height * image->width * sizeof(uint32_t);
	while (pixelstart < pixelend)
	{
		pixelstart[3] = 0xFF;
		pixelstart += image->width * sizeof(uint32_t);
	}
}

void
	draw_raycast(
		void *param)
{
	t_scene		*scene;
	t_ray		ray;
	uint32_t	screen_x;

	scene = param;
	if (scene->recast == false)
		return ;
	reset_image(scene->walls);
	screen_x = 0;
	while (screen_x < scene->walls->width)
	{
		ray.camera_x = 2 * screen_x / (float)scene->walls->width - 1;
		init_ray(&ray, &scene->camera);
		cast_ray(&ray, scene);
		draw_ray(scene->walls, screen_x, scene->walls->height / 2 / ray.distance);
		++screen_x;
	}
}
