/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   menu_scene_set_ability.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/19 00:40:10 by simon         #+#    #+#                 */
/*   Updated: 2025/04/21 21:57:10 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	set_menu_ability(
		t_menu *menu,
		bool ability)
{
	size_t	i;

	menu->background.image->enabled = ability;
	i = 0;
	while (i < MENU_B_COUNT)
		menu->buttons[i++].image->enabled = ability;
	menu->highlight.image->enabled = ability;
}

void
	set_scene_ability(
		t_scene *scene,
		t_weapon *weapon,
		bool ability)
{
	scene->walls.image->enabled = ability;
	weapon->display_img->enabled = ability;
}
