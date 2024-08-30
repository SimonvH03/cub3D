/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_draw_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 01:36:33 by simon             #+#    #+#             */
/*   Updated: 2024/08/30 03:16:47 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static uint32_t
	transform_minimap_pixel(
		t_minimap *minimap,
		int x,
		int y)
{
	float		scale = minimap->side / minimap->scene->y_max;

	x /= scale;
	y /= scale;
	if (x < 0 || x >= minimap->scene->x_max
		|| y < 0 || y >= minimap->scene->y_max)
		return (C_CEILING);
	if (minimap->scene->map[y][x] > 0)
		return (C_WALL);
	return (C_FLOOR);
}

void
	draw_minimap(
		void *param)
{
	t_minimap	*minimap;
	uint32_t	y;
	uint32_t	x;
	uint32_t	colour;

	minimap = param;
	y = minimap->inner_side;
	while (y < minimap->side - minimap->inner_side)
	{
		x = minimap->inner_side;
		while (x < minimap->side - minimap->inner_side)
		{
			// if (is_in_circle(minimap->x_offset, minimap->y_offset,
			// 	minimap->radius, x, y) == true)
			// {
				colour = transform_minimap_pixel(minimap, x, y);
				mlx_put_pixel(minimap->walls, x, y, colour);
			// }
			++x;
		}
		++y;
	}
}
