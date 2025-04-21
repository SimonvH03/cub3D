/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hudmap_setget_ability.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/19 00:31:12 by simon         #+#    #+#                 */
/*   Updated: 2025/04/21 22:33:34 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// set bigmap image group enabled bit
void
	set_bigmap_ability(
		t_bigmap *bigmap,
		bool ability)
{
	bigmap->walls->enabled = ability;
	bigmap->player->enabled = ability;
}

bool
	get_bigmap_ability(
		t_bigmap *bigmap)
{
	return (bigmap->walls->enabled);
}

// set minimap image group enabled bit
void
	set_minimap_ability(
		t_minimap *minimap,
		bool ability)
{
	minimap->walls->enabled = ability;
	minimap->player.image->enabled = ability;
}

bool
	get_minimap_ability(
		t_minimap *minimap)
{
	return (minimap->walls->enabled);
}
