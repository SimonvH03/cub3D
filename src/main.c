/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:33:20 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/27 21:50:11 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// Phase 2: keyhook
// 			scrollhook
// 			user_inputs
// Phase 3: raycast
// Phase 4: draw
static void
	loop_hooks(
		t_cub3d *cub3d)
{
	mlx_key_hook(cub3d->mlx, &keyhook, cub3d);
	// mlx_scroll_hook(cub3d->mlx, &scrollhook, cub3d);
	mlx_loop_hook(cub3d->mlx, &user_inputs, cub3d);
	mlx_loop_hook(cub3d->mlx, &raycast, cub3d);
	// mlx_loop_hook(cub3d->mlx, &draw, cub3d);
}

// Phase 1: scene_init
// 			cub3d_init
// 			menu_draw
int
	main(
		int argc,
		char **argv)
{
	t_cub3d			cub3d;
	t_scene			scene;
	t_camera			camera;

	if (argc != 2)
		return (EXIT_FAILURE);
	if (cub3d_init(&cub3d, &scene, &camera, argv[1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// menu_draw(&cub3d);
	loop_hooks(&cub3d);
	// raycast(&cub3d);
	mlx_loop(cub3d.mlx);
	mlx_terminate(cub3d.mlx);
	scene_free(&scene);
	return (EXIT_SUCCESS);
}
