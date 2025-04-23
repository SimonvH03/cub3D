/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/31 18:33:20 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/04/22 01:43:00 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory_cub3d.h"

static void
	frametime_dependant_variables(
		void *param)
{
	t_window	*window;
	double		delta_time;
	t_camera	*camera;

	window = (t_window *)param;
	delta_time = window->mlx->delta_time;
	camera = &window->camera;
	camera->movement_speed = MOVEMENT_SPEED * delta_time;
	if (camera->movement_speed > 0.5f)
		camera->movement_speed = 0.5f;
	camera->rotation_cosin[0] = cosf(ROTATION_SPEED * delta_time);
	camera->rotation_cosin[1] = sinf(ROTATION_SPEED * delta_time);
}

void
	view_manager(
		void *param)
{
	t_window	*window;

	window = param;
	wasd_move(window->mlx, &window->scene.grid, &window->camera);
	arrowkey_look(window->mlx, &window->camera);
	raycast(&window->scene, &window->camera);
}

static void	link_loop_hooks(t_window *window)
{
	mlx_key_hook(window->mlx, window_keyhook, window);
	mlx_loop_hook(window->mlx, frametime_dependant_variables, window);
	mlx_loop_hook(window->mlx, view_manager, window);
}

static void	cub3d_terminate(t_window *window)
{
	mlx_terminate(window->mlx);
	ft_arrclear((void **)window->scene.grid.tilemap);
	empty_texture_list(window);
}

int	main(int argc, char **argv)
{
	t_window	window;

	ft_bzero(&window, sizeof(t_window));
	if (argc != 2)
	{
		printf("Usage:\n%s <path/to/scene.cub>\n", argv[0]);
		return (EINVAL);
	}
	if (init_window(&window) != RETURN_SUCCESS)
	{
		print_error();
		return (RETURN_FAILURE);
	}
	if (init_game(&window, &window.scene, argv[1]) == RETURN_SUCCESS)
	{
		link_loop_hooks(&window);
		mlx_loop(window.mlx);
	}
	cub3d_terminate(&window);
	if (mlx_errno || g_cub_errno)
		print_error();
	return (mlx_errno || g_cub_errno);
}
