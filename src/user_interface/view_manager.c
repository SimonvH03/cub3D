/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   view_manager.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/31 18:33:20 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/04/21 22:23:40 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	view_manager(
		void *param)
{
	t_window	*window;
	mlx_t		*mlx;

	window = param;
	mlx = window->mlx;
	if (window->view == wv_game)
	{
		wasd_move(mlx, &window->scene.grid, &window->player.camera);
		arrowkey_look(mlx, &window->player.camera);
		mouse_pan(mlx, &window->player.camera);
		update_doors(&window->scene.grid, mlx->delta_time);
		raycast(&window->scene, &window->player.camera);
		update_weapon(mlx, &window->player.weapon);
		update_minimap(&window->hud.minimap);
		update_bigmap(&window->hud.bigmap);
	}
	else if (window->view == wv_menu)
	{
		hover_button(&window->menu, window);
	}
}

void
	toggle_maps(
		t_hud *hud)
{
	set_minimap_ability(&hud->minimap, !get_minimap_ability(&hud->minimap));
	set_bigmap_ability(&hud->bigmap, !get_bigmap_ability(&hud->bigmap));
}

void
	toggle_view(
		t_window *window)
{
	bool	game_img;

	if (window->view == wv_menu)
	{
		window->view = wv_game;
		mlx_set_cursor_mode(window->mlx, MLX_MOUSE_HIDDEN);
		mlx_set_mouse_pos(window->mlx,
			window->mlx->width / 2, window->mlx->height / 2);
	}
	else if (window->view == wv_game)
	{
		window->view = wv_menu;
		mlx_set_cursor_mode(window->mlx, MLX_MOUSE_NORMAL);
	}
	game_img = (bool)(window->view == wv_game);
	set_menu_ability(&window->menu, !game_img);
	set_scene_ability(&window->scene, &window->player.weapon, game_img);
	set_minimap_ability(&window->hud.minimap, game_img);
	set_bigmap_ability(&window->hud.bigmap, false);
}
