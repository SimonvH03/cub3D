/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:21:01 by simon             #+#    #+#             */
/*   Updated: 2024/09/16 17:59:08 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// void
// 	print_camera(
// 		t_camera *camera)
// {
// 	printf("\e[33mCAM INIT\e[0m\t[%-10f, %-10f]\ndir  -->\t[%-10f,
//	 %-10f]\nplane <->\t[%-10f, %-10f]\n",
// 		camera->pos_y, camera->pos_x, camera->dir_y, camera->dir_x,
//		camera->plane_y, camera->plane_x);
// }

// void
// 	print_ray(
// 		t_ray *ray)
// {
// 	printf("\e[33mRAY INIT\e[0m\t[%-10d, %-10d]\ndir  -->\t[%-10f, 
//	 %-10f]\nstep <->\t[%-10f, %-10f]\ntotal<->\t[%-10f, %-10f]\n",
// 		ray->pos_y, ray->pos_x, ray->dir_y, ray->dir_x, ray->step_y,
//		ray->step_x, ray->total_y, ray->total_x);
// }

// void
// 	print_minimap(
// 		t_minimap *minimap)
// {
// 	printf("\e[33mMinimap Init\e[0m\nside:\t%d\nradius:\t%d\nscale:\t%f\n",
// 		minimap->side, minimap->radius, minimap->scale);
// 	printf("\e[32mScene\e[0m\nx_max\t%d\ny_max\t%d\n",
// 		minimap->r_scene->x_max, minimap->r_scene->y_max);
// }

// void
// 	print_content(
// 		t_scene *scene)
// {
// 	int	i;

// 	i = 0;
// 	while (scene->content[i])
// 	{
// 		printf("%s\n", scene->content[i]);
// 		++i;
// 	}
// }

// void
// 	print_map(
// 		t_scene *scene)
// {
// 	int	y;
// 	int	x;

// 	printf("\e[33mmap size: %d * %d\e[0m\n", scene->y_max, scene->x_max);
// 	y = 0;
// 	while (y < scene->y_max)
// 	{
// 		printf("%p\t", scene->map[y]);
// 		x = 0;
// 		if (scene->map[y])
// 		{
// 			while (x < scene->x_max)
// 			{
// 				if (scene->map[y][x] == 0)
// 					printf("  ");
// 				else
// 					printf("\e[34mX \e[0m");
// 				++x;
// 			}
// 		}
// 		printf("\n");
// 		++y;
// 	}
// }

// void
// 	draw_textures(
// 		t_window *window)
// {
// 	mlx_image_t	*image;

// 	image = mlx_texture_to_image(window->mlx, window->scene.north_texture);
// 	mlx_image_to_window(window->mlx, image, 128, 64);
// 	image = mlx_texture_to_image(window->mlx, window->scene.east_texture);
// 	mlx_image_to_window(window->mlx, image, 192, 128);
// 	image = mlx_texture_to_image(window->mlx, window->scene.south_texture);
// 	mlx_image_to_window(window->mlx, image, 128, 192);
// 	image = mlx_texture_to_image(window->mlx, window->scene.west_texture);
// 	mlx_image_to_window(window->mlx, image, 64, 128);
// }
