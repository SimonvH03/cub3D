/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_raycast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 01:36:33 by simon             #+#    #+#             */
/*   Updated: 2024/08/28 22:06:31 by simon            ###   ########.fr       */
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
	// print_ray(ray);
}

// assuming the camera is not inside a wall;
//	shift map position to the nearest (total_y <> total_x) grid line;
//	and check wall type (0 or positive int 1-N)
static float
	cast_ray(
		t_ray *ray,
		t_scene *scene)
{
	// while (true)// true crashes if casting skips walls or map is not enclosed in walls
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
	return (ft_max_float(ray->total_y - ray->step_y, ray->total_x - ray->step_x));
}

void
	draw_ray(
		mlx_image_t *image,
		uint32_t screen_x,
		float distance)
{
	const uint32_t	half_height = image->height / 2;
	uint32_t		wall_height;
	uint32_t		y;

	wall_height = image->height / distance;
	if (wall_height > image->height)
		wall_height = image->height;
	y = 0;
	while (y < wall_height / 2)
	{
		// mlx_put_pixel(image, screen_x, (image->height / 2) + y, gradient(height / (float)image->height, C_CEILING, C_WALL));
		// mlx_put_pixel(image, screen_x, (image->height / 2) - y, gradient(height / (float)image->height, C_CEILING, C_WALL));
		mlx_put_pixel(image, screen_x, half_height + y, C_WALL);
		mlx_put_pixel(image, screen_x, half_height - y, C_WALL);
		++y;
	}
}

void
	raycast(
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
		// printf("\e[33mSCREEN_X %d\e[0m\ncamera_x %d/%d\ndistance %f\n\n", screen_x, (int)(camera_x * WIDTH), WIDTH, distance);
		draw_ray(scene->walls, screen_x, distance);
		++screen_x;
	}
	scene->recast = false;
}
