/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/31 18:33:20 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/05/12 18:09:31 by svan-hoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cub3d_terminate(t_window *window)
{
	mlx_terminate(window->mlx);
	mlx_destroy_cursor(window->cursor);
	ft_arrclear((void **)window->scene.grid.tilemap);
	empty_texture_list(window);
	free(window->player.weapon.fire);
	free(window->player.weapon.reload);
	free(window->scene.grid.door_list);
	free((void *)window->hud.minimap.circle_overlay);
}

static void	link_loop_hooks(t_window *window)
{
	mlx_key_hook(window->mlx, window_keyhook, window);
	mlx_loop_hook(window->mlx, frametime_dependant_variables, window);
	mlx_loop_hook(window->mlx, view_manager, window);
	mlx_mouse_hook(window->mlx, mouse_buttons, window);
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
	if (init_game(&window, &window.scene, argv[1]) == RETURN_SUCCESS
		&& init_weapon(&window, &window.player.weapon) == RETURN_SUCCESS
		&& init_menu(&window, &window.menu) == RETURN_SUCCESS
		&& set_view_depths(&window) == RETURN_SUCCESS)
	{
		link_loop_hooks(&window);
		mlx_loop(window.mlx);
	}
	cub3d_terminate(&window);
	if (mlx_errno || g_cub_errno)
		print_error();
	return (mlx_errno || g_cub_errno);
}
