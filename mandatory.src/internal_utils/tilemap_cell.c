/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tilemap_cell.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:51:01 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/04/22 17:49:47 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory_cub3d.h"

char
	set_tilemap_cell(
		const char type)
{
	return (((bool)0 << FLOOD_SHIFT) | (type & TYPE_MASK));
}

char
	get_type(const char cell)
{
	return ((char)(cell & TYPE_MASK));
}
