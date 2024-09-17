/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu_images.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/09/17 02:02:42 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static uint32_t
	get_scaled_pixel_colour(
		t_scalable *scalable,
		float x,
		float y)
{
	mlx_texture_t	*texture;
	uint32_t		index;
	uint8_t			*pixelstart;

	texture = scalable->texture;
	x /= scalable->scale;
	y /= scalable->scale;
	if (x < 0 || x >= texture->width
		|| y < 0 || y >= texture->height)
		return (0x00000000);
	index = ((int)y * texture->width + (int)x) * sizeof(uint32_t);
	pixelstart = &texture->pixels[index];
	return ((uint32_t)(pixelstart[0] << 24 | pixelstart[1] << 16
		| pixelstart[2] << 8 | pixelstart[3]));
}

void
	draw_scaled_image(
		t_scalable *scalable)
{
	uint32_t	y;
	uint32_t	x;
	uint32_t	colour;

	y = 0;
	while (y < scalable->image->height)
	{
		x = 0;
		while (x < scalable->image->width)
		{
			colour = get_scaled_pixel_colour(scalable, x, y);
			mlx_put_pixel(scalable->image, x, y, colour);
			++x;
		}
		++y;
	}
}

// void
// 	draw_menu_highlight(
// 		mlx_image_t *image)
// {
// 	uint32_t	y;
// 	uint32_t	x;

// 	y = 0;
// 	while (y < image->height)
// 	{
// 		x = 0;
// 		while (x < image->width)
// 		{
// 			mlx_put_pixel(image, x, y, C_HIGHLIGHT);
// 			++x;
// 		}
// 		++y;
// 	}
// }
