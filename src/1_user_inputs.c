/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_user_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:05:56 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/29 14:47:55 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void
	scene_recast(
		t_window *window)
{
	if (mlx_is_key_down(window->mlx, MLX_KEY_R)
		|| mlx_is_key_down(window->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(window->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(window->mlx, MLX_KEY_W)
		|| mlx_is_key_down(window->mlx, MLX_KEY_A)
		|| mlx_is_key_down(window->mlx, MLX_KEY_S)
		|| mlx_is_key_down(window->mlx, MLX_KEY_D))
		window->scene.recast = true;
}

static void
	arrowkey_turn(
		t_window	*window)
{
	if (mlx_is_key_down(window->mlx, MLX_KEY_LEFT))
		window->scene.camera.precalc.sign_alpha = 1;
	if (mlx_is_key_down(window->mlx, MLX_KEY_RIGHT))
		window->scene.camera.precalc.sign_alpha = -1;
	rotate_camera(&window->scene.camera);
}

void
	user_inputs(
		void	*param)
{
	t_window	*window;

	window = param;
	wasd_move(window);
	arrowkey_turn(window);
	scene_recast(window);
}
