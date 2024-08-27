/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/08/27 20:27:16 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// used by menu_draw() and draw()
// creates a background
// creates a blank canvas over previous points
void
	draw_background(
		mlx_image_t *image,
		t_scene *scene)
{
	uint32_t	y;
	uint32_t	x;

	y = 0;
	while (y < image->height / 2)
	{
		x = 0;
		while (x < image->width)
		{
			mlx_put_pixel((mlx_image_t *)image, x, y, scene->ceiling);
			x++;
		}
		++y;
	}
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
		{
			mlx_put_pixel((mlx_image_t *)image, x, y, scene->floor);
			x++;
		}
		++y;
	}
}

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
