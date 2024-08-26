/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:05:50 by simon             #+#    #+#             */
/*   Updated: 2024/08/26 18:05:12 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void
	draw_orthogonally_adjacent(
		void *param,
		const int y,
		const int x)
{
	const t_cub3d		*cub3d = param;
	const t_point	*p0 = &cub3d->map->project[y][x];
	const int		p0_check = draw_check_point(cub3d, p0->x, p0->y);
	t_point			*p1;

	if ((x + 1) < cub3d->map->x_max)
	{
		p1 = &cub3d->map->project[y][x + 1];
		if (!p0_check || !draw_check_point(cub3d, p1->x, p1->y))
			draw_line(cub3d, p0, p1);
	}
	if ((y + 1) < cub3d->map->y_max)
	{
		p1 = &cub3d->map->project[y + 1][x];
		if (!p0_check || !draw_check_point(cub3d, p1->x, p1->y))
			draw_line(cub3d, p0, p1);
	}
	if ((x + 1) == cub3d->map->x_max && cub3d->ballin == true)
	{
		p1 = &cub3d->map->project[y][0];
		if (!p0_check || !draw_check_point(cub3d, p1->x, p1->y))
			draw_line(cub3d, p0, p1);
	}
}

// from loop_hooks
void
	draw(
		void *param)
{
	t_cub3d	*cub3d;

	cub3d = param;
	if (cub3d->redraw == false)
		return ;
	draw_background(cub3d->image, cub3d->map->palette.background);
	map_iteration(cub3d->map, &draw_orthogonally_adjacent, cub3d);
	cub3d->redraw = false;
}
