/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_doors.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 16:58:42 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/04/19 01:08:05 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int
	init_door(
		t_door *dest,
		t_grid *grid,
		unsigned int pos_y,
		unsigned int pos_x)
{
	int16_t	north_cell;
	int16_t	south_cell;
	int16_t	east_cell;
	int16_t	west_cell;

	dest->r_cell = &grid->tilemap[pos_y][pos_x];
	north_cell = grid->tilemap[pos_y - 1][pos_x];
	south_cell = grid->tilemap[pos_y + 1][pos_x];
	east_cell = grid->tilemap[pos_y][pos_x + 1];
	west_cell = grid->tilemap[pos_y][pos_x - 1];
	if (is_solid(north_cell) && is_solid(south_cell))
		*dest->r_cell &= ~AXIS_MASK;
	else if (is_solid(east_cell) && is_solid(west_cell))
		*dest->r_cell |= AXIS_MASK;
	else
		return (set_error(CUB_INVDOOR));
	dest->position = 1.0f;
	dest->state = ds_closed;
	dest->pos_y = pos_y;
	dest->pos_x = pos_x;
	return (RETURN_SUCCESS);
}

static int
	fill_door_list(
		t_grid *grid,
		unsigned int y,
		unsigned int x,
		void *param)
{
	unsigned int	*door_index;
	char			type;

	door_index = param;
	type = get_type(grid->tilemap[y][x]);
	if (type == 'd' || type == 'D')
	{
		if (init_door(&grid->door_list[(*door_index)++], grid, y, x)
			!= RETURN_SUCCESS)
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

int
	init_doors(
		t_grid *grid)
{
	unsigned int	door_index;

	if (grid->door_count == 0)
		return (RETURN_SUCCESS);
	grid->door_list = (t_door *)malloc(grid->door_count * sizeof(t_door));
	if (grid->door_list == NULL)
		return (set_error(CUB_MEMFAIL));
	door_index = 0;
	if (gridmap_iter(grid, fill_door_list, &door_index) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}
