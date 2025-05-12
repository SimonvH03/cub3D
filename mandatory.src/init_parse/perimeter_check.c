/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   perimeter_check.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/15 20:50:32 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/05/12 18:30:27 by svan-hoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory_cub3d.h"

static bool
	visited(const char cell)
{
	return ((bool)(cell & FLOOD_MASK));
}

bool
	flood_fill(
		t_grid *grid,
		int y,
		int x)
{
	if (x < 0 || x >= (int)grid->x_max || y < 0 || y >= (int)grid->y_max)
		return (false);
	if (visited(grid->tilemap[y][x]))
		return (true);
	grid->tilemap[y][x] |= FLOOD_MASK;
	if (get_type(grid->tilemap[y][x]) == ' ')
		return (false);
	if (get_type(grid->tilemap[y][x]) == '1')
		return (true);
	return (flood_fill(grid, y + 1, x)
		&& flood_fill(grid, y - 1, x)
		&& flood_fill(grid, y, x + 1)
		&& flood_fill(grid, y, x - 1));
}

int
	perimeter_check(
		t_grid *grid,
		unsigned int y,
		unsigned int x,
		void *param)
{
	(void)param;
	if (!visited(grid->tilemap[y][x])
		&& (ft_strchr("NESW", get_type(grid->tilemap[y][x]))
		|| get_type(grid->tilemap[y][x]) == '0'))
	{
		if (!flood_fill(grid, y, x))
			return (set_error(CUB_MAPPERIM));
	}
	return (RETURN_SUCCESS);
}
