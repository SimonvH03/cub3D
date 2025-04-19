/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tilemap_cell.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:51:01 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/04/19 21:43:43 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
