/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/08/27 01:52:41 by simon            ###   ########.fr       */
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
	uint32_t	i;
	uint32_t	j;

	j = 0;
	while (j < image->height)
	{
		i = 0;
		while (i < image->width / 2)
		{
			mlx_put_pixel((mlx_image_t *)image, i, j, scene->ceiling);
			i++;
		}
		while (i < image->width)
		{
			mlx_put_pixel((mlx_image_t *)image, i, j, scene->floor);
			i++;
		}
		j++;
	}
}
