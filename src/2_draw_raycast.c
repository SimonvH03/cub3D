/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_draw_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 01:36:33 by simon             #+#    #+#             */
/*   Updated: 2024/09/10 00:12:29 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// camera plane * 0.5 for perfect cubes
static void
	init_ray(
		t_ray *ray,
		t_camera *camera)
{
	ray->pos_x = (int)camera->pos_x;
	ray->pos_y = (int)camera->pos_y;
	ray->dir_x = camera->dir_x + camera->plane_x * 0.5 * ray->camera_x;
	ray->dir_y = camera->dir_y + camera->plane_y * 0.5 * ray->camera_x;
	ray->step_x = ft_abs_float(1 / ray->dir_x);
	if (ray->step_x == INFINITY)
		ray->step_x = UINT32_MAX;
	ray->step_y = ft_abs_float(1 / ray->dir_y);
	if (ray->step_y == INFINITY)
		ray->step_y = UINT32_MAX;
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
	ray->distance = 0;
}

// assuming the camera is not inside a wall;
//	shift map position to the nearest (total_y <> total_x) grid line;
//	and check wall type (-1, 0 or positive int 1-N)
static void
	cast_ray(
		t_ray *ray,
		t_scene *scene)
{
	while (ray->pos_x && ray->pos_x < scene->x_max
		&& ray->pos_y && ray->pos_y < scene->y_max)
	{
		if (ray->total_x < ray->total_y)
		{
			ray->total_x += ray->step_x;
			ray->pos_x += ray->sign_x;
			ray->hit_type = HORIZONTAL;
		}
		else
		{
			ray->total_y += ray->step_y;
			ray->pos_y += ray->sign_y;
			ray->hit_type = VERTICAL;
		}
		if (scene->map[ray->pos_y][ray->pos_x] > 0)
			break ;
	}
	if (ray->hit_type == HORIZONTAL)
		ray->distance = ray->total_x - ray->step_x;
	else
		ray->distance = ray->total_y - ray->step_y;
}

static uint32_t
	get_ray_pixel_colour(
		mlx_texture_t *texture,
		uint32_t tex_x,
		uint32_t tex_y)
{
	uint32_t	colour;
	uint32_t	index;
	uint8_t		*texel;

	if (tex_y >= texture->height)
		return (C_ERROR);
	index = tex_y * texture->width + tex_x;
	texel = &texture->pixels[index * texture->bytes_per_pixel];
	colour = texel[0] << 24 | texel[1] << 16 | texel[2] << 8 | texel[3];
	return (colour);
}

static void
	draw_ray(
		t_scene *scene,
		t_ray *ray,
		uint32_t x)
{
	int				wall_height;
	uint32_t		y;
	int				start;
	int				end;
	mlx_texture_t	*texture;
	float			wall_x;
	uint32_t		tex_x;
	double			step;
	double			pos_y;
	uint32_t		tex_y;
	uint32_t		colour;

	wall_height = scene->walls->height / ray->distance;
	start = (int)(scene->walls->height - wall_height) / 2;
	if (start < 0)
		start = 0;
	end = (scene->walls->height + wall_height) / 2;
	if (end >= scene->walls->height)
		end = scene->walls->height;
	if (ray->hit_type == HORIZONTAL)
	{
		if (ray->sign_x > 0)
			texture = scene->east_texture;
		else
			texture = scene->west_texture;
		wall_x = scene->camera.pos_y + ray->distance * ray->dir_y;
	}
	else
	{
		if (ray->sign_y > 0)
			texture = scene->south_texture;
		else
			texture = scene->north_texture;
		wall_x = scene->camera.pos_x + ray->distance * ray->dir_x;
	}
	wall_x -= (int)wall_x;
	tex_x = wall_x * texture->width;
	if (ray->hit_type == HORIZONTAL && ray->sign_x > 0
		|| ray->hit_type == VERTICAL && ray->sign_y < 0)
		tex_x = texture->width - 1 - tex_x;
	step = texture->height / (double)wall_height;
	pos_y = (start - (int)scene->walls->height / 2 + wall_height / 2) * step;
	y = (uint32_t)start;
	while (y < (uint32_t)end)
	{
		tex_y = (int)pos_y & (texture->height - 1);
		pos_y += step;
		colour = get_ray_pixel_colour(texture, tex_x, tex_y);
		mlx_put_pixel(scene->walls, x, y, colour);
		++y;
	}
}

void
	draw_raycast(
		t_scene *scene)
{
	t_ray		ray;
	uint32_t	x;

	if (scene->recast == false)
		return ;
	reset_image(scene->walls);
	x = 0;
	while (x < scene->walls->width)
	{
		ray.camera_x = 2 * x / (float)scene->walls->width - 1;
		init_ray(&ray, &scene->camera);
		cast_ray(&ray, scene);
		draw_ray(scene, &ray, x);
		++x;
	}
}


// {01, 02, 03, 04, 05, 06, 07, 08, 09}
// {11, 12, 13, 14, 15, 16, 17, 18, 19}
// {21, 22, 23, 24, 25, 26, 27, 28, 29}
// {31, 32, 33, 34, 35, 36, 37, 38, 39}
// {41, 42, 43, 44, 45, 46, 47, 48, 49}
// {51, 52, 53, 54, 55, 56, 57, 58, 59}
// {61, 62, 63, 64, 65, 66, 67, 68, 69}
// {71, 72, 73, 74, 75, 76, 77, 78, 79}
// {81, 82, 83, 84, 85, 86, 87, 88, 89}
// {91, 92, 93, 94, 95, 96, 97, 98, 99}