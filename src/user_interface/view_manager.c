/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferid <ferid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:33:20 by svan-hoo          #+#    #+#             */
/*   Updated: 2025/01/21 21:23:57 by ferid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void
	view_manager(
		void *param)
{
	t_window	*window;

	window = param;
	if (window->view == GAME)
	{
		wasd_move(window, &window->scene.camera);
		arrowkey_turn(window, &window->scene.camera);
		update_door_animations(&window->scene, window->mlx->delta_time);

		// Check for G key to start weapon animation
		if (mlx_is_key_down(window->mlx, MLX_KEY_G))
			start_weapon_animation(&window->scene);

		// Check for R key to start reload animation
		if (mlx_is_key_down(window->mlx, MLX_KEY_R))
			start_reload_animation(&window->scene);

		// Update weapon animation if it's in progress
		if (window->scene.weapon.is_animating || window->scene.weapon.is_reloading)
			next_weapon_frame(&window->scene, window->mlx->delta_time);

		if (window->scene.recast == true)
		{
			draw_raycast(&window->scene);
			if (window->minimap.enabled == true)
				draw_minimap_walls(&window->minimap);
			if (window->map.enabled == true)
				draw_map_player(&window->map);
			window->scene.recast = false;
		}
	}
}

void
	toggle_maps(
		t_minimap *minimap,
		t_map *map)
{
	minimap->player->enabled = !minimap->player->enabled;
	minimap->walls->enabled = !minimap->walls->enabled;
	minimap->enabled = !minimap->enabled;
	map->player->enabled = !map->player->enabled;
	map->walls->enabled = !map->walls->enabled;
	map->enabled = !map->enabled;
	map->r_scene->recast = true;
}

void
	toggle_view(
		t_window *window)
{
	size_t	i;

	if (window->view == MENU)
		window->view = GAME;
	else if (window->view == GAME)
		window->view = MENU;
	window->menu.background.image->enabled
		= !window->menu.background.image->enabled;
	window->menu.highlight.image->enabled
		= !window->menu.highlight.image->enabled;
	i = 0;
	while (i < MENU_B_COUNT)
	{
		window->menu.buttons[i].image->enabled
			= !window->menu.buttons[i].image->enabled;
		++i;
	}
}
