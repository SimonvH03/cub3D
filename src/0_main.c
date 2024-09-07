/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:33:20 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/07 03:44:02 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void
	view_manager(
		void *param)
{
	t_window	*window;

	window = param;
	if (window->view == GAME)
	{
		// if (window->map.enabled == true)
		// 	map_inputs(window);
		// else
			game_inputs(window);
		if (window->scene.recast == true)
		{
			draw_raycast(&window->scene);
			// if (window->map.enabled == true)
			// 	draw_map(&window->map);
			// else
				draw_minimap(&window->minimap);
		}
	}
	// else if (window->view == MENU)
	// {
	// 	menu_inputs(window);
	// 	if (window->menu.interaction_highlight)
	// 	draw_menu(&window->menu);
	// }
}

static void
	loop_hooks(
		t_window *window)
{
	mlx_loop_hook(window->mlx, &update_time, window);
	mlx_key_hook(window->mlx, &keyhook, window);
	// mlx_scroll_hook(window->mlx, &scrollhook, window);
	mlx_loop_hook(window->mlx, &view_manager, window);
}

int
	main(
		int argc,
		char **argv)
{
	t_window			window;

	if (argc != 2)
		return (EXIT_FAILURE);
	if (init_structs(&window, argv[1]) == EXIT_FAILURE
		|| init_images(&window) == EXIT_FAILURE)
		error_exit(mlx_errno, 0, "initialisation failed");
	draw_textures(&window);// test
	loop_hooks(&window);
	mlx_loop(window.mlx);
	mlx_terminate(window.mlx);
	scene_free(&window.scene);
	return (EXIT_SUCCESS);
}

void
	error_exit(
		mlx_errno_t mlx_errno,
		int custom_errno,
		char *message)
{
	if (custom_errno == 0)
		custom_errno = errno;
	if (write(STDERR_FILENO, "Error\n", 7) == -1)
		exit(errno);
	if (mlx_errno)
		printf("mlx_errno: %d: %s\n", mlx_errno, mlx_strerror(mlx_errno));
	if (custom_errno)
		printf("custom_errno: %d: %s\n", custom_errno, strerror(custom_errno));
	if (message)
		printf("message: %s\n", message);
	// set_them_free();
	exit(errno);
}
