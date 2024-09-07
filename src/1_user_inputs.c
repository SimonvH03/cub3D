/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_user_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:05:56 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/07 01:12:27 by simon            ###   ########.fr       */
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

void
	game_inputs(
		void	*param)
{
	t_window	*window;

	window = param;
	wasd_move(window);
	arrowkey_turn(window);
	scene_recast(window);
}

// from main.c / loop_hooks()
void
	keyhook(
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

// void
// 	scrollhook(
// 		double xdelta,
// 		double ydelta,
// 		void *param)
// {
// 	t_window	*window;

// 	window = param;
// }

void
	update_time(
		void	*param)
{
	t_window	*window;

	window = param;
	window->deltatime = mlx_get_time() - window->time;
	window->time = mlx_get_time();
	reset_image(window->fps);
	modlx_replace_string(window->fps, ft_itoa(1 / window->deltatime));
}
