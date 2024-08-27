/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/08/27 20:03:58 by simon            ###   ########.fr       */
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
		while (x < image->width / 2)
		{
			mlx_put_pixel((mlx_image_t *)image, x, y, scene->ceiling);
			x++;
		}
		++y;
	}
	while (y < image->height / 2)
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
