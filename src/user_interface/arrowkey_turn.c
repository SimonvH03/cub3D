/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrowkey_turn.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 23:30:28 by simon             #+#    #+#             */
/*   Updated: 2024/09/16 22:56:15 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void
	rotate_camera(
		t_camera *camera)
{
	const float	previous_x = camera->dir_x;
	const float	rm[2][2] = {{camera->rotation_cosin[0],
		camera->rotation_cosin[1] * camera->sign_rotate},
	{-camera->rotation_cosin[1] * camera->sign_rotate,
		camera->rotation_cosin[0]}};

	camera->dir_x = camera->dir_x * rm[0][0] + camera->dir_y * rm[0][1];
	camera->dir_y = previous_x * rm[1][0] + camera->dir_y * rm[1][1];
	camera->plane_x = CAMERA_PLANE * camera->aspect_ratio * -camera->dir_y;
	camera->plane_y = CAMERA_PLANE * camera->aspect_ratio * camera->dir_x;
	camera->sign_rotate = 0;
}

void
	arrowkey_turn(
		t_window	*window,
		t_camera *camera)
{
	if (mlx_is_key_down(window->mlx, MLX_KEY_LEFT))
		camera->sign_rotate = 1;
	if (mlx_is_key_down(window->mlx, MLX_KEY_RIGHT))
		camera->sign_rotate = -1;
	if (camera->sign_rotate != 0)
	{
		rotate_camera(camera);
		window->scene.recast = true;
	}
}
