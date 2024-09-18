/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:05:56 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/18 17:51:00 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void
	game_keys(
		mlx_key_data_t keydata,
		t_window *window)
{
	if ((keydata.key == MLX_KEY_M || keydata.key == MLX_KEY_TAB)
		&& keydata.action == MLX_PRESS)
	{
		toggle_maps(&window->minimap, &window->map);
	}
	if (keydata.key == MLX_KEY_LEFT_CONTROL && keydata.action == MLX_PRESS)
	{
		toggle_view(window);
	}
}

static void
	menu_keys(
		mlx_key_data_t keydata,
		t_window *window)
{
	if ((keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN)
		&& keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_UP
			&& window->menu.selection > 0)
			window->menu.selection -= 1;
		if (keydata.key == MLX_KEY_DOWN
			&& window->menu.selection < MENU_B_COUNT - 1)
			window->menu.selection += 1;
		up_down_select(&window->menu);
	}
	if ((keydata.key == MLX_KEY_ENTER || keydata.key == MLX_KEY_SPACE)
		&& keydata.action == MLX_PRESS)
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
	if (window->view == GAME)
	{
		game_keys(keydata, window);
	}
	else if (window->view == MENU)
	{
		menu_keys(keydata, window);
	}
}
