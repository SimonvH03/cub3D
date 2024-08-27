/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:05:56 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/28 01:38:44 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void
	cub3d_redraw(
		t_cub3d *cub3d)
{
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_R)
		|| mlx_is_key_down(cub3d->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(cub3d->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(cub3d->mlx, MLX_KEY_W)
		|| mlx_is_key_down(cub3d->mlx, MLX_KEY_A)
		|| mlx_is_key_down(cub3d->mlx, MLX_KEY_S)
		|| mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
		cub3d->redraw = true;
}

static void
	wasd_move(
		t_cub3d	*cub3d)
{
	t_camera *camera;

	camera = cub3d->scene->camera;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
	{
		camera->pos_y += camera->dir_y * camera->movement_speed;
		camera->pos_x += camera->dir_x * camera->movement_speed;
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
	{
		camera->pos_y -= camera->dir_y * camera->movement_speed;
		camera->pos_x -= camera->dir_x * camera->movement_speed;
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
	{
		camera->pos_y += camera->dir_x * camera->movement_speed;
		camera->pos_x -= camera->dir_y * camera->movement_speed;
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
	{
		camera->pos_y -= camera->dir_x * camera->movement_speed;
		camera->pos_x += camera->dir_y * camera->movement_speed;
	}
}

static void
	arrowkey_turn(
		t_cub3d	*cub3d)
{
	t_camera *camera;

	camera = cub3d->scene->camera;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_LEFT))
		camera->precalc.sign_alpha = -1;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_RIGHT))
		camera->precalc.sign_alpha = 1;
	rotate_camera(camera);
}

void
	user_inputs(
		void	*param)
{
	t_cub3d	*cub3d;

	cub3d = param;
	wasd_move(cub3d);
	arrowkey_turn(cub3d);
	cub3d_redraw(cub3d);
}
