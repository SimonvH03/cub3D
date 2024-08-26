/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/08/26 18:05:12 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// used by menu_draw() and draw()
// creates a background
// creates a blank canvas over previous points
void
	draw_background(
		const mlx_image_t *image,
		const uint32_t colour)
{
	uint32_t	i;
	uint32_t	j;

	j = 0;
	while (j < image->height)
	{
		i = 0;
		while (i < image->width)
		{
			mlx_put_pixel((mlx_image_t *)image, i, j, colour);
			i++;
		}
		j++;
	}
}

// used by map_colour() and draw_line_pixel()
// determines single point or pixel colour on a scale
uint32_t
	gradient(
		double ratio,
		uint32_t start,
		uint32_t end)
{
	const t_colour_construct	c0 = (t_colour_construct)
	{(start >> 24) & 0xFF,
		(start >> 16) & 0xFF,
		(start >> 8) & 0xFF,
		start & 0xFF};
	const t_colour_construct	c1 = (t_colour_construct)
	{(end >> 24) & 0xFF,
		(end >> 16) & 0xFF,
		(end >> 8) & 0xFF,
		end & 0xFF};
	const t_colour_construct	res = (t_colour_construct)
	{(unsigned int)(c1.r * ratio) + (c0.r * (1 - ratio)),
		(unsigned int)(c1.g * ratio) + (c0.g * (1 - ratio)),
		(unsigned int)(c1.b * ratio) + (c0.b * (1 - ratio)),
		(unsigned int)(c1.a * ratio) + (c0.a * (1 - ratio))};

	return ((uint32_t)((res.r << 24) | (res.g << 16) | (res.b << 8) | res.a));
}

// used by draw_adjacent() and draw_line_pixel()
// determines whether a point or pixel would be projected inside the image
int
	draw_check_point(
		const t_cub3d *cub3d,
		int x_pixel,
		int y_pixel)
{
	x_pixel += cub3d->center.x + cub3d->offset.x;
	y_pixel += cub3d->center.y + cub3d->offset.y;
	if (x_pixel < 0 || y_pixel < 0
		|| x_pixel >= (int)cub3d->image->width
		|| y_pixel >= (int)cub3d->image->height)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}
