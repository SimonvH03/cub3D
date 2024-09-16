/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:33:20 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/16 17:14:51 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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
	if (window->view == MENU)
		window->view = GAME;
	else if (window->view == GAME)
		window->view = MENU;
	window->menu.background.image->enabled
		= !window->menu.background.image->enabled;
	window->menu.button_start.image->enabled
		= !window->menu.button_start.image->enabled;
	window->menu.button_quit.image->enabled
		= !window->menu.button_quit.image->enabled;
}

void
	view_manager(
		void *param)
{
	t_window	*window;

	window = param;
	if (window->view == GAME)
	{
		game_inputs(window);
		if (window->scene.recast == true)
		{
			draw_raycast(&window->scene);
			if (window->minimap.enabled == true)
				draw_minimap_walls(&window->minimap);
			if (window->map.enabled == true)
				draw_map_player(&window->map);
		}
		window->scene.recast = false;
	}
	// else if (window->view == MENU)
	// {
	// 	menu_inputs(window);
	// 	if (window->menu.interaction_highlight)
	// 	draw_menu(&window->menu);
	// }
}
