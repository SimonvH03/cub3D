/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tilemap_type.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:51:01 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/04/19 22:12:49 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool
	is_door(const int16_t cell)
{
	const char	type = get_type(cell);

	return ((bool)(type == 'd' || type == 'D'));
}

bool
	is_wall(const int16_t cell)
{
	const char	type = get_type(cell);

	return ((bool)(type > '0' && type <= '9'));
}
