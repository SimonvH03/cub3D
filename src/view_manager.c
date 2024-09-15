/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:33:20 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/15 19:23:30 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void
	toggle_menu_images(
		t_menu *menu)
{
	menu->background.image->enabled = !menu->background.image->enabled;
	menu->button_start.image->enabled = !menu->button_start.image->enabled;
	menu->button_quit.image->enabled = !menu->button_quit.image->enabled;
}

void
	toggle_view(
		t_window *window)
{
	if (window->view == MENU)
		window->view = GAME;
	else if (window->view == GAME)
		window->view = MENU;
	toggle_menu_images(&window->menu);
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
				draw_minimap(&window->minimap);
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
