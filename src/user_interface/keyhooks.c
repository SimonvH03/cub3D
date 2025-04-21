/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyhooks.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/09 19:05:56 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/04/21 21:55:58 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	game_keys(
		mlx_key_data_t keydata,
		t_window *window)
{
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_M || keydata.key == MLX_KEY_TAB)
	{
		toggle_maps(&window->hud);
	}
	if (keydata.key == MLX_KEY_LEFT_CONTROL)
	{
		toggle_view(window);
	}
	if (keydata.key == MLX_KEY_E)
	{
		player_interaction(&window->scene.grid, &window->player.camera);
	}
	if (keydata.key == MLX_KEY_G)
	{
		fire_weapon(&window->player.weapon);
	}
	if (keydata.key == MLX_KEY_R)
	{
		reload_weapon(&window->player.weapon);
	}
}

static void
	menu_keys(
		mlx_key_data_t keydata,
		t_window *window)
{
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN)
	{
		select_button(&window->menu, keydata.key);
	}
	if (keydata.key == MLX_KEY_ENTER || keydata.key == MLX_KEY_SPACE)
	{
		confirm_selection(&window->menu, window);
	}
}

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
	if (window->view == wv_game)
	{
		game_keys(keydata, window);
	}
	else if (window->view == wv_menu)
	{
		menu_keys(keydata, window);
	}
}
