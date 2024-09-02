/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_draw_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 01:36:33 by simon             #+#    #+#             */
/*   Updated: 2024/09/01 16:14:23 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void
	init_ray(
		t_ray *ray,
		float camera_x,
		t_camera *camera)
{
	ray->pos_y = (int)camera->pos_y;
	ray->pos_x = (int)camera->pos_x;
	ray->dir_y = camera->dir_y + camera->plane_y * camera_x;
	ray->dir_x = camera->dir_x + camera->plane_x * camera_x;
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
}

// assuming the camera is not inside a wall;
//	shift map position to the nearest (total_y <> total_x) grid line;
//	and check wall type (0 or positive int 1-N)
static float
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
		if (scene->map[ray->pos_y][ray->pos_x])
			break ;
	}
	if (ray->step_y == INFINITY)
		return (ray->total_x - ray->step_x);
	if (ray->step_x == INFINITY)
		return (ray->total_y - ray->step_y);
	return (ft_max_float(ray->total_y - ray->step_y, ray->total_x - ray->step_x));
}

static void
	draw_ray(
		mlx_image_t *image,
		uint32_t screen_x,
		float distance)
{
	const uint32_t	half_height = image->height / 2;
	uint32_t		wall_height;
	uint32_t		y;
	uint32_t		colour;

	wall_height = image->height / distance;
	if (wall_height > image->height)
		wall_height = image->height;
	colour = gradient(wall_height / (float)image->height, C_CEILING, C_WALL);
	y = 0;
	while (y < wall_height / 2)
	{
		mlx_put_pixel(image, screen_x, half_height + y, colour);
		mlx_put_pixel(image, screen_x, half_height - y, colour);
		++y;
	}
}

void
	draw_raycast(
		void *param)
{
	t_scene		*scene;
	uint32_t	screen_x;
	t_ray		ray;
	float		camera_x;
	float		distance;

	scene = param;
	if (scene->recast == false)
		return ;
	reset_image(scene->walls);
	screen_x = 0;
	while (screen_x < scene->walls->width)
	{
		camera_x = 2 * screen_x / (float)scene->walls->width - 1;
		init_ray(&ray, camera_x, &scene->camera);
		distance = cast_ray(&ray, scene);
		draw_ray(scene->walls, screen_x, distance);
		++screen_x;
	}
}
