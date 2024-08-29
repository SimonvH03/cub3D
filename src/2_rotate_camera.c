/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_rotate_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 23:30:28 by simon             #+#    #+#             */
/*   Updated: 2024/08/30 01:05:51 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void
	rotate_camera(
		t_camera *camera)
{
	const float	previous_x = camera->dir_x;
	const float	prev_plane_x = camera->plane_x;
	const float	rm[2][2] = {camera->rm[0], camera->rm[1] * camera->sign_rotate,
		-camera->rm[1] * camera->sign_rotate, camera->rm[0]};

	if (camera->sign_rotate == 0)
		return ;
	camera->dir_x = camera->dir_x * rm[0][0] + camera->dir_y * rm[0][1];
	camera->dir_y = previous_x * rm[1][0] + camera->dir_y * rm[1][1];
	camera->plane_x = CAMERA_PLANE * -camera->dir_y;
	camera->plane_y = CAMERA_PLANE * camera->dir_x;
	camera->sign_rotate = 0;
}
