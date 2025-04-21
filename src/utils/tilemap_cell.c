/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tilemap_cell.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:51:01 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/04/21 22:37:24 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int16_t
	set_tilemap_cell(
		const bool solid,
		const int id,
		const char type)
{
	return ((solid << SOLID_SHIFT)
		| ((bool)0 << AXIS_SHIFT)
		| ((id & 0x7F) << ID_SHIFT)
		| (type & TYPE_MASK));
}

bool
	is_solid(const int16_t cell)
{
	return ((bool)(cell & SOLID_MASK));
}

bool
	get_axis(const int16_t cell)
{
	return ((bool)(cell & AXIS_MASK));
}

char
	get_type(const int16_t cell)
{
	return ((char)(cell & TYPE_MASK));
}

int
	get_id(const int16_t cell)
{
	return ((int)((cell & ID_MASK) >> ID_SHIFT));
}
