/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_down_select.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 23:36:30 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/18 17:52:58 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void
	up_down_select(
		t_menu *menu)
{
	menu->highlight.image->instances[0].x
		= menu->buttons[menu->selection].image->instances[0].x;
	menu->highlight.image->instances[0].y
		= menu->buttons[menu->selection].image->instances[0].y;
}

void
	confirm_selection(
		t_menu *menu,
		t_window *window)
{
	if (menu->selection == MENU_B_START_INDEX)
		toggle_view(window);
	if (menu->selection == MENU_B_QUIT_INDEX)
		mlx_close_window(window->mlx);
}
