/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 22:07:27 by simon             #+#    #+#             */
/*   Updated: 2024/09/01 16:17:13 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void
	reset_image(
		mlx_image_t *image)
{
	uint32_t	pixel_count;
	uint8_t		*dst;
	uint32_t	limit;

	pixel_count = 0;
	dst = image->pixels;
	limit = image->height * image->width;
	while (pixel_count < limit)
	{
		dst[3] = 0x00;
		++pixel_count;
		dst += sizeof(uint32_t);
	}
}

// void // need to test which of these is faster: while checking (uint32_t) or checking (uint_8_t *)
// 	reset_image(
// 		mlx_image_t *image)
// {
// 	uint8_t		*dst;
// 	uint8_t		*dst_limit;

// 	dst = image->pixels;
// 	dst_limit = dst + image->height * image->width * sizeof(uint32_t);
// 	while (dst < dst_limit)
// 	{
// 		dst[3] = 0x00;
// 		dst += sizeof(uint32_t);
// 	}
// }

uint32_t
	gradient(
		float ratio,
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
