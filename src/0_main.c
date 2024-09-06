/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:33:20 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/06 01:39:33 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

static void
	loop_hooks(
		t_window *window)
{
	mlx_key_hook(window->mlx, &keyhook, window);
	// mlx_scroll_hook(window->mlx, &scrollhook, window);
	mlx_loop_hook(window->mlx, &update_time, window);
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
		return (perror(mlx_strerror(mlx_errno)), EXIT_FAILURE);
	draw_textures(&window);
	loop_hooks(&window);
	mlx_loop(window.mlx);
	mlx_terminate(window.mlx);
	scene_free(&window.scene);
	return (EXIT_SUCCESS);
}
