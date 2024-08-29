/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_draw_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 01:36:33 by simon             #+#    #+#             */
/*   Updated: 2024/08/30 01:17:00 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void
	transform_minimap_pixel()
{
}

void
	raycast(
		void *param)
{
	t_minimap	*minimap;
	uint32_t	y;
	uint32_t	x;

	minimap = param;
	x = 0;
	while (x < minimap->width)
	{
		y = 0;
		while (y < minimap->height)
		{
			if (is_in_circle(minimap->x_offset, minimap->y_offset,
				minimap->radius, x, y) == false)
				transfrom_minimap_pixel();
			++y;
		}
		++x;
	}
}
