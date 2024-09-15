/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:33:20 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/15 16:52:23 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void
	update_time(
		void	*param)
{
	t_window	*window;
	t_camera	*camera;

	window = param;
	camera = &window->scene.camera;
	window->deltatime = mlx_get_time() - window->time;
	window->time = mlx_get_time();
	reset_image(window->fps);
	modlx_replace_string(window->fps, ft_itoa(1 / window->deltatime));
	camera->movement_speed = MOVEMENT_SPEED * window->deltatime;
	if (camera->movement_speed > 0.49)
		camera->movement_speed = 0.49;
	camera->rotation_cosin[0] = cosf(ROTATION_SPEED * window->deltatime);
	camera->rotation_cosin[1] = sinf(ROTATION_SPEED * window->deltatime);
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
	t_window	window;

	if (argc != 2)
		return (EXIT_FAILURE);
	if (init_game_structs(&window, argv[1]) == EXIT_FAILURE
		|| init_game_images(&window) == EXIT_FAILURE
		|| init_scalables(&window) == EXIT_FAILURE
		|| init_menu_images(&window) == EXIT_FAILURE)
		error_exit(mlx_errno, 0, "initialisation failed");
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
		printf("mlx_errno: %3d: %s\n", mlx_errno, mlx_strerror(mlx_errno));
	if (custom_errno)
		printf("std_errno: %3d: %s\n", custom_errno, strerror(custom_errno));
	if (message)
		printf("message  :    : %s\n", message);
	// set_them_free();
	exit(errno);
}
