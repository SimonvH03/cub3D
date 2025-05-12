/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   perimeter_check.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/15 20:50:32 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/05/12 18:28:32 by svan-hoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool
	visited(int16_t cell)
{
	return (get_axis(cell) == (bool)1);
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
	grid->tilemap[y][x] |= AXIS_MASK;
	if (get_type(grid->tilemap[y][x]) == ' ')
		return (false);
	if (get_type(grid->tilemap[y][x]) == '1')
		return (true);
	return (flood_fill(grid, y + 1, x)
		&& flood_fill(grid, y - 1, x)
		&& flood_fill(grid, y, x + 1)
		&& flood_fill(grid, y, x - 1));
}

// must be ran before init_doors: uses cell axis bit to mark visited cells
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
		|| get_type(grid->tilemap[y][x]) == '0'
		|| is_door(grid->tilemap[y][x])))
	{
		if (!flood_fill(grid, y, x))
			return (set_error(CUB_PERIM));
	}
	return (RETURN_SUCCESS);
}
