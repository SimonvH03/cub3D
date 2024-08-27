/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:21:01 by simon             #+#    #+#             */
/*   Updated: 2024/08/27 18:48:09 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void
	print_camera(
		t_camera *camera)
{
	printf("\e[33mCAM INIT\e[0m\t[%-10f, %-10f]\ndir  -->\t[%-10f, %-10f]\nplane <->\t[%-10f, %-10f]\n",
		camera->pos_y, camera->pos_x, camera->dir_y, camera->dir_x, camera->plane_y, camera->plane_x);
}

void
	print_map(
		t_scene *scene)
{
	int	y;
	int	x;

	printf("\e[33mmap size: %d * %d\e[0m\n", scene->y_max, scene->x_max);
	y = 0;
	while (y < scene->y_max)
	{
		printf("%p\t", scene->map[y]);
		x = 0;
		if (scene->map[y])
			while (x < scene->x_max)
			{
				if (scene->map[y][x] == 0)
					printf("  ");
				else
					printf("\e[34mX \e[0m");
				++x;
			}
		printf("\n");
		++y;
	}
}

void
	print_ray(
		t_ray *ray)
{
	printf("\e[33mRAY INIT\e[0m\t[%-10d, %-10d]\ndir  -->\t[%-10f, %-10f]\nstep <->\t[%-10f, %-10f]\ntotal<->\t[%-10f, %-10f]\n",
		ray->pos_y, ray->pos_x, ray->dir_y, ray->dir_x, ray->step_y, ray->step_x, ray->total_y, ray->total_x);
}
