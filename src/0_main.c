/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:33:20 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/01 14:34:03 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void
	loop_hooks(
		t_window *window)
{
	mlx_key_hook(window->mlx, &keyhook, window);
	// mlx_scroll_hook(window->mlx, &scrollhook, window);
	mlx_loop_hook(window->mlx, &user_inputs, window);
	mlx_loop_hook(window->mlx, &draw_raycast, &window->scene);
	mlx_loop_hook(window->mlx, &draw_minimap, &window->minimap);
	// mlx_loop_hook(window->mlx, &draw, window);
}

int
	main(
		int argc,
		char **argv)
{
	t_window			window;

	if (argc != 2)
		return (EXIT_FAILURE);
	if (init(&window, argv[1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	loop_hooks(&window);
	mlx_loop(window.mlx);
	mlx_terminate(window.mlx);
	scene_free(&window.scene);
	return (EXIT_SUCCESS);
}
