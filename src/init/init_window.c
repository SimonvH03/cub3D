/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_window.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:49:26 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/08/06 17:34:58 by simon         ########   odam.nl         */
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

void
	set_image_depth(
		mlx_image_t *image,
		int32_t	depth)
{
	size_t	i;

	i = 0;
	while (i < image->count)
		image->instances[i++].z = depth;
}

int
	set_view_depths(
		t_window *window)
{
	int32_t	depth;
	size_t	i;

	depth = 0;
	set_image_depth(window->scene.walls.image, depth++);
	set_image_depth(window->player.weapon.display_img, depth++);
	set_image_depth(window->hud.bigmap.walls, depth++);
	set_image_depth(window->hud.bigmap.player, depth++);
	set_image_depth(window->hud.minimap.walls, depth++);
	set_image_depth(window->hud.minimap.player.image, depth++);
	set_image_depth(window->menu.background.image, depth++);
	i = 0;
	while (i < MENU_B_COUNT)
		set_image_depth(window->menu.buttons[i++].image, depth++);
	set_image_depth(window->menu.highlight.image, depth++);
	set_image_depth(window->hud.fps.image, depth++);
	sort_queue = true;
	window->view = wv_menu;
	return (RETURN_SUCCESS);
}
