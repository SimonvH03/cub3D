/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_arrowkey_turn.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 23:30:28 by simon             #+#    #+#             */
/*   Updated: 2024/09/08 18:39:37 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void
	rotate_camera(
		t_camera *camera)
{
	const double	previous_x = camera->dir_x;
	const double	prev_plane_x = camera->plane_x;
	const double	rm[2][2] = {camera->rm[0], camera->rm[1] * camera->sign_rotate,
		-camera->rm[1] * camera->sign_rotate, camera->rm[0]};

	if (camera->sign_rotate == 0)
		return ;
	camera->dir_x = camera->dir_x * rm[0][0] + camera->dir_y * rm[0][1];
	camera->dir_y = previous_x * rm[1][0] + camera->dir_y * rm[1][1];
	camera->plane_x = CAMERA_PLANE * -camera->dir_y;
	camera->plane_y = CAMERA_PLANE * camera->dir_x;
	camera->sign_rotate = 0;
}

void
	arrowkey_turn(
		t_window	*window)
{
	if (mlx_is_key_down(window->mlx, MLX_KEY_LEFT))
		window->scene.camera.sign_rotate = 1;
	if (mlx_is_key_down(window->mlx, MLX_KEY_RIGHT))
		window->scene.camera.sign_rotate = -1;
	rotate_camera(&window->scene.camera);
}
