/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyboard_controls.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/09 19:05:56 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/04/22 02:09:25 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory_cub3d.h"

void
	window_keyhook(
		mlx_key_data_t keydata,
		void *param)
{
	t_window	*window;

	window = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(window->mlx);
	}
}

// looks up the sin and cosin values based on which of the 8 directions
//	(9 if you count 0, 0) the player can move
// each directions has precalculated normalized x and y direction components
//  based on the unit circle /pythagoras because why bother with cos45 or sin45
// !this function assumes the camera is not currently outside of the tilemap
static void
	move_camera(
		t_camera *camera,
		char **tilemap,
		short forward_backward,
		short left_right)
{
	float	cos_sin[2];
	float	move_dir_x;
	float	move_dir_y;
	float	hitbox_x;
	float	hitbox_y;

	cos_sin[0] = camera->movement_matrix[1 + left_right][1 + forward_backward];
	cos_sin[1] = camera->movement_matrix[1 + forward_backward][1 + left_right];
	move_dir_x = camera->dir_x * cos_sin[0] + camera->dir_y * -cos_sin[1];
	move_dir_y = camera->dir_x * cos_sin[1] + camera->dir_y * cos_sin[0];
	hitbox_x = COLLISION_HITBOX * ft_sign_float(move_dir_x);
	hitbox_y = COLLISION_HITBOX * ft_sign_float(move_dir_y);
	if (tilemap[(int)camera->pos_y][(int)(camera->pos_x + hitbox_x
			+ move_dir_x * camera->movement_speed)] == '1')
		move_dir_x = (int)camera->pos_x - camera->pos_x + (move_dir_x > 0)
			- hitbox_x;
	if (tilemap[(int)(camera->pos_y + hitbox_y
				+ move_dir_y * camera->movement_speed)][(int)camera->pos_x] == '1')
		move_dir_y = (int)camera->pos_y - camera->pos_y + (move_dir_y > 0)
			- hitbox_y;
	camera->pos_x += move_dir_x * camera->movement_speed;
	camera->pos_y += move_dir_y * camera->movement_speed;
}

void
	wasd_move(
		mlx_t *mlx,
		t_grid *grid,
		t_camera *camera)
{
	short	forward_backward;
	short	left_right;

	forward_backward = 0;
	left_right = 0;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		forward_backward += 1;
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		forward_backward -= 1;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		left_right -= 1;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		left_right += 1;
	if (forward_backward || left_right)
		move_camera(camera, grid->tilemap, forward_backward, left_right);
}

static void
	rotate_camera(
		t_camera *camera,
		short left_right)
{
	const float	previous_x = camera->dir_x;
	const float	rm[2][2] = {{camera->rotation_cosin[0],
		camera->rotation_cosin[1] * left_right},
	{-camera->rotation_cosin[1] * left_right,
		camera->rotation_cosin[0]}};

	camera->dir_x = camera->dir_x * rm[0][0] + camera->dir_y * rm[0][1];
	camera->dir_y = previous_x * rm[1][0] + camera->dir_y * rm[1][1];
	normalize_vector2(&camera->dir_x, &camera->dir_y);
	camera->plane_x = CAMERA_PLANE * camera->aspect_ratio * -camera->dir_y;
	camera->plane_y = CAMERA_PLANE * camera->aspect_ratio * camera->dir_x;
}

void
	arrowkey_look(
		mlx_t *mlx,
		t_camera *camera)
{
	short	left_right;

	left_right = 0;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		left_right += 1;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		left_right -= 1;
	if (left_right != 0)
	{
		rotate_camera(camera, left_right);
	}
}
