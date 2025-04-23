/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_window.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:49:26 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/04/22 17:50:36 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory_cub3d.h"

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
	return (RETURN_SUCCESS);
}
