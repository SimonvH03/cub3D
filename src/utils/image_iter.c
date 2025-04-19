/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   image_iter.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/28 22:07:27 by simon         #+#    #+#                 */
/*   Updated: 2025/02/25 02:26:46 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	image_iter(
		mlx_image_t	*image,
		imgiter_func function,
		void *param)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
		{
			function(image, x, y, param);
			x++;
		}
		y++;
	}
}
