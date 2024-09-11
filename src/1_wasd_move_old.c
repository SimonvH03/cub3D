/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_wasd_move_old.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:05:56 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/11 00:58:47 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../cub3d.h"

// static void
// 	move_forward(
// 		t_scene *scene,
// 		t_camera *camera)
// {
// 	const float	next_y = camera->pos_y + ft_sign_float(camera->dir_y) * 0.125;
// 	const float	next_x = camera->pos_x + ft_sign_float(camera->dir_x) * 0.125;

// 	if (scene->map[(int)next_y][(int)camera->pos_x] <= 0)
// 		camera->pos_y += camera->dir_y * camera->movement_speed;
// 	else if (camera->dir_y > 0)
// 		camera->pos_y = (int)(camera->pos_y + 1) - 0.124;
// 	else
// 		camera->pos_y = (int)camera->pos_y + 0.124;
// 	if (scene->map[(int)camera->pos_y][(int)next_x] <= 0)
// 		camera->pos_x += camera->dir_x * camera->movement_speed;
// 	else if (camera->dir_x > 0)
// 		camera->pos_x = (int)(camera->pos_x + 1) - 0.124;
// 	else
// 		camera->pos_x = (int)camera->pos_x + 0.124;
// }

// static void
// 	move_backward(
// 		t_scene *scene,
// 		t_camera *camera)
// {
// 	const float	next_y = camera->pos_y - ft_sign_float(camera->dir_y) * 0.125;
// 	const float	next_x = camera->pos_x - ft_sign_float(camera->dir_x) * 0.125;


// 	if (scene->map[(int)next_y][(int)camera->pos_x] <= 0)
// 		camera->pos_y -= camera->dir_y * camera->movement_speed;
// 	else if (camera->dir_y <= 0)
// 		camera->pos_y = (int)(camera->pos_y + 1) - 0.124;
// 	else
// 		camera->pos_y = (int)camera->pos_y + 0.124;
// 	if (scene->map[(int)camera->pos_y][(int)next_x] <= 0)
// 		camera->pos_x -= camera->dir_x * camera->movement_speed;
// 	else if (camera->dir_x <= 0)
// 		camera->pos_x = (int)(camera->pos_x + 1) - 0.124;
// 	else
// 		camera->pos_x = (int)camera->pos_x + 0.124;
// }

// static void
// 	move_right(
// 		t_scene *scene,
// 		t_camera *camera)
// {
// 	const float	next_y = camera->pos_y
// 		+ (ft_sign_float(camera->dir_x) / (float)8);
// 	const float	next_x = camera->pos_x
// 		- (ft_sign_float(camera->dir_y) / (float)8);

// 	if (scene->map[(int)next_y][(int)camera->pos_x] <= 0)
// 		camera->pos_y += camera->dir_x * camera->movement_speed;
// 	if (scene->map[(int)camera->pos_y][(int)next_x] <= 0)
// 		camera->pos_x -= camera->dir_y * camera->movement_speed;
// }

// static void
// 	move_left(
// 		t_scene *scene,
// 		t_camera *camera)
// {
// 	const float	next_y = camera->pos_y
// 		- (ft_sign_float(camera->dir_x) / (float)8);
// 	const float	next_x = camera->pos_x
// 		+ (ft_sign_float(camera->dir_y) / (float)8);

// 	if (scene->map[(int)next_y][(int)camera->pos_x] <= 0)
// 		camera->pos_y -= camera->dir_x * camera->movement_speed;
// 	if (scene->map[(int)camera->pos_y][(int)next_x] <= 0)
// 		camera->pos_x += camera->dir_y * camera->movement_speed;
// }

// void
// 	wasd_move(
// 		t_window	*window)
// {
// 	short	diagonal_correction;

// 	diagonal_correction = 0;
// 	if (mlx_is_key_down(window->mlx, MLX_KEY_W))
// 		diagonal_correction += 1;
// 	if (mlx_is_key_down(window->mlx, MLX_KEY_S))
// 		diagonal_correction += 1;
// 	if (mlx_is_key_down(window->mlx, MLX_KEY_D))
// 		diagonal_correction += 2;
// 	if (mlx_is_key_down(window->mlx, MLX_KEY_A))
// 		diagonal_correction += 2;
// 	if (diagonal_correction % 3 == 0)
// 		window->scene.camera.movement_speed /= sqrt(2);
// 	if (mlx_is_key_down(window->mlx, MLX_KEY_W))
// 		move_forward(&window->scene, &window->scene.camera);
// 	if (mlx_is_key_down(window->mlx, MLX_KEY_S))
// 		move_backward(&window->scene, &window->scene.camera);
// 	if (mlx_is_key_down(window->mlx, MLX_KEY_D))
// 		move_right(&window->scene, &window->scene.camera);
// 	if (mlx_is_key_down(window->mlx, MLX_KEY_A))
// 		move_left(&window->scene, &window->scene.camera);
// 	if (diagonal_correction % 3 == 0)
// 		window->scene.camera.movement_speed *= sqrt(2);
// }
