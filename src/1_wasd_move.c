/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_wasd_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:05:56 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/11 14:41:26 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// I'm really proud of this one, basically you look up the sin and cosin values
//	based on which of the 8 directions (9 if you count 0, 0) you want to move
// each directions has precalculated normalized x and y direction components
//  based on the unit circle /pythagoras because why bother with cos45 or sin45
// !this function assumes the camera is not currently outside of the map
static void
	do_movement(
		t_camera *camera,
		int	**map,
		short forward_backward,
		short left_right)
{
	float	move_dir_x;
	float	move_dir_y;
	float	cos_sin[2];
	float	wall_dist_x;
	float	wall_dist_y;

	cos_sin[0] = camera->movement_matrix[1 + left_right][1 + forward_backward];
	cos_sin[1] = camera->movement_matrix[1 + forward_backward][1 + left_right];
	move_dir_x = camera->dir_x * cos_sin[0] + camera->dir_y * -cos_sin[1];
	move_dir_y = camera->dir_x * cos_sin[1] + camera->dir_y * cos_sin[0];
	if (move_dir_x > 0)
		wall_dist_x = camera->pos_x - ((int)camera->pos_x + 1);
	else
		wall_dist_x = camera->pos_x - (int)camera->pos_x;
	if (move_dir_y > 0)
		wall_dist_y = camera->pos_y - ((int)camera->pos_y + 1);
	else
		wall_dist_y = camera->pos_y - (int)camera->pos_y;
	if (map[(int)camera->pos_y][(int)(camera->pos_x + move_dir_x * camera->movement_speed)])
		move_dir_x = -ft_max_abs_float(move_dir_x, wall_dist_x);
	if (map[(int)(camera->pos_y + move_dir_y * camera->movement_speed)][(int)camera->pos_x])
		move_dir_y = -ft_max_abs_float(move_dir_y, wall_dist_y);
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
		do_movement(camera, window->scene.map, forward_backward, left_right);
}
