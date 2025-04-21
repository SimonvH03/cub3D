/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_window.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:49:26 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/04/21 22:41:15 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	init_window(
		t_window *window)
{
	int32_t	width;
	int32_t	height;

	mlx_set_setting(MLX_STRETCH_IMAGE, false);
	mlx_set_setting(MLX_FULLSCREEN, false);
	mlx_set_setting(MLX_MAXIMIZED, FULLSCREEN);
	mlx_set_setting(MLX_DECORATED, !FULLSCREEN);
	mlx_set_setting(MLX_HEADLESS, false);
	window->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, false);
	if (window->mlx == NULL)
		return (set_error(CUB_MEMFAIL));
	if (FULLSCREEN == true)
	{
		mlx_get_monitor_size(MONITOR_ID, &width, &height);
		mlx_set_window_size(window->mlx, width, height);
	}
	mlx_set_mouse_pos(window->mlx, window->mlx->width / 2,
		window->mlx->height / 2);
	window->cursor = mlx_create_std_cursor(MLX_CURSOR_ARROW);
	mlx_set_cursor(window->mlx, window->cursor);
	return (RETURN_SUCCESS);
}

int
	set_view_depths(
		t_window *window)
{
	int32_t	depth;
	size_t	i;

	depth = 0;
	window->scene.walls.image->instances[0].z = depth++;
	window->player.weapon.display_img->instances[0].z = depth++;
	window->hud.bigmap.walls->instances[0].z = depth++;
	window->hud.bigmap.player->instances[0].z = depth++;
	window->hud.minimap.walls->instances[0].z = depth++;
	window->hud.minimap.player.image->instances[0].z = depth++;
	window->menu.background.image->instances[0].z = depth++;
	i = 0;
	while (i < MENU_B_COUNT)
		window->menu.buttons[i++].image->instances[0].z = depth++;
	window->menu.highlight.image->instances[0].z = depth++;
	window->hud.fps.image->instances[0].z = depth++;
	sort_queue = true;
	window->view = wv_menu;
	return (RETURN_SUCCESS);
}
