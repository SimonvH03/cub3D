/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gridmap_iter.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/16 21:02:53 by simon         #+#    #+#                 */
/*   Updated: 2025/04/21 23:54:46 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory_cub3d.h"

int
	gridmap_iter(
		t_grid *grid,
		griditer_func function,
		void *param)
{
	unsigned int	y;
	unsigned int	x;
	int				return_value;

	return_value = RETURN_FAILURE;
	y = 0;
	while (y < grid->y_max)
	{
		x = 0;
		while (x < grid->x_max)
		{
			return_value = function(grid, y, x, param);
			if (return_value != RETURN_SUCCESS)
				return (return_value);
			x++;
		}
		y++;
	}
	return (RETURN_SUCCESS);
}
