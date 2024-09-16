/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modlx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 22:07:27 by simon             #+#    #+#             */
/*   Updated: 2024/09/16 17:12:23 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void
	mlx_draw_char(
		mlx_image_t *image,
		int32_t texoffset,
		int32_t imgoffset)
{
	char		*pixelx;
	uint8_t		*pixeli;
	uint32_t	y;

	if (texoffset < 0)
		return ;
	y = 0;
	while (y < FONT_HEIGHT)
	{
		pixelx = &font_atlas.pixels[(y * font_atlas.width + texoffset) * BPP];
		pixeli = image->pixels + ((y * image->width + imgoffset) * BPP);
		ft_memcpy(pixeli, pixelx, FONT_WIDTH * BPP);
		++y;
	}
}

void
	modlx_reset_image(
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

void
	modlx_replace_string(
		mlx_image_t *strimage,
		const char *str)
{
	const size_t	len = strlen(str);
	int32_t			imgoffset;
	size_t			i;

	modlx_reset_image(strimage);
	imgoffset = 0;
	i = 0;
	while (i < len)
	{
		mlx_draw_char(strimage, mlx_get_texoffset(str[i]), imgoffset);
		imgoffset += FONT_WIDTH;
		i++;
	}
}
