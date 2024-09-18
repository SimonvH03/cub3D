/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:33:20 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/18 17:51:08 by svan-hoo         ###   ########.fr       */
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
