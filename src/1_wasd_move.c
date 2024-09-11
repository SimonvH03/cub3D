/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_wasd_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:05:56 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/11 02:28:27 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// I'm really proud of this one, basically you look up the sin and cosin values
//	based on which of the 8 directions (9 if you count 0, 0) you want to move
// each directions has precalculated normalized x and y direction components
//  based on the unit circle /pythagoras because why bother with cos45 or sin45
static void
	do_movement(
		t_camera *camera,
		short forward_backward,
		short left_right)
{
	float move_dir_x;
	float move_dir_y;
	float cos_sin[2];

	cos_sin[0] = camera->movement_matrix[1 + left_right][1 + forward_backward];
	cos_sin[1] = camera->movement_matrix[1 + forward_backward][1 + left_right];
	move_dir_x = camera->dir_x * cos_sin[0] + camera->dir_y * -cos_sin[1];
	move_dir_y = camera->dir_x * cos_sin[1] + camera->dir_y * cos_sin[0];
	camera->pos_x += move_dir_x * camera->movement_speed;
	camera->pos_y += move_dir_y * camera->movement_speed;
}

void
	wasd_move(
		t_window *window,
		t_camera *camera)
{
	short forward_backward;
	short left_right;

	forward_backward = 0;
	left_right = 0;
	if (mlx_is_key_down(window->mlx, MLX_KEY_W))
		forward_backward += 1;
	if (mlx_is_key_down(window->mlx, MLX_KEY_S))
		forward_backward -= 1;
	if (mlx_is_key_down(window->mlx, MLX_KEY_A))
		left_right -= 1;
	if (mlx_is_key_down(window->mlx, MLX_KEY_D))
		left_right += 1;
	if (forward_backward || left_right)
		do_movement(camera, forward_backward, left_right);
}
