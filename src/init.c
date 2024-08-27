/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:49:26 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/27 19:26:01 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void
	camera_init(
		t_camera *camera,
		int pos_y,
		int pos_x,
		char direction)
{
	camera->movement_speed = MOVEMENT_SPEED;
	camera->rotation_speed = ROTATION_SPEED;
	camera->pos_y = pos_y + 0.5;
	camera->pos_x = pos_x + 0.5;
	if (direction == 'N')
		camera->dir_y = -1,
		camera->dir_x = 0;
	if (direction == 'E')
		camera->dir_y = 0,
		camera->dir_x = 1;
	if (direction == 'S')
		camera->dir_y = 1,
		camera->dir_x = 0;
	if (direction == 'W')
		camera->dir_y = 0,
		camera->dir_x = -1;
	camera->plane_x = CAMERA_PLANE * camera->dir_y;
	camera->plane_y = CAMERA_PLANE * camera->dir_x;
	print_camera(camera);
}

static short
	cub3d_mlx_init(
		t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init(WIDTH, HEIGHT, WINDOW_TITLE, false);
	if (cub3d->mlx == NULL)
		return (EXIT_FAILURE);
	cub3d->image = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (cub3d->image == NULL)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(cub3d->mlx, cub3d->image, 0, 0) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// from main.c / main()
short
	cub3d_init(
		t_cub3d *cub3d,
		t_scene *scene,
		t_camera *camera,
		char *cub)
{
	if (cub3d_mlx_init(cub3d) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	scene->camera = camera;
	scene->name = cub;
	scene->map = NULL;
	scene->fd = 0;
	if (map_read(scene) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	cub3d->scene = scene;
	return (EXIT_SUCCESS);
}
