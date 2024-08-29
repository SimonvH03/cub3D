/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_draw_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 01:36:33 by simon             #+#    #+#             */
/*   Updated: 2024/08/29 22:46:17 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void
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
		draw_ray(scene->walls, screen_x, distance);
		++screen_x;
	}
	scene->recast = false;
}
