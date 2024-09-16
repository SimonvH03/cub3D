/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modlx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 22:07:27 by simon             #+#    #+#             */
/*   Updated: 2024/09/16 17:52:21 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void
	reset_image(
		mlx_image_t *image)
{
	uint8_t		*dst;
	uint8_t		*dst_limit;

	dst = image->pixels;
	dst_limit = dst + image->height * image->width * sizeof(uint32_t);
	while (dst < dst_limit)
	{
		dst[3] = 0x00;
		dst += sizeof(uint32_t);
	}
}
