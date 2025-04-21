/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   modlx.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/28 22:07:27 by simon         #+#    #+#                 */
/*   Updated: 2025/04/21 22:30:27 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "MLX42/src/font/font.h"

// duplicates an mlx_texture_t
static mlx_texture_t	*
	modlx_texdup(
		mlx_texture_t *src)
{
	size_t			pixelcount;
	mlx_texture_t	*dest;

	if (src == NULL)
		return (NULL);
	dest = malloc(sizeof(mlx_texture_t));
	if (dest == NULL)
		return (NULL);
	dest->width = src->width;
	dest->height = src->height;
	dest->bytes_per_pixel = src->bytes_per_pixel;
	dest->pixels = malloc(src->width * src->height
			* sizeof(uint8_t) * src->bytes_per_pixel);
	if (dest->pixels == NULL)
	{
		free(dest);
		return (NULL);
	}
	pixelcount = src->width * src->height;
	ft_memcpy(dest->pixels, src->pixels, pixelcount * sizeof(uint32_t));
	return (dest);
}

// loads xpm and properly deletes it, not strictly necessary in current version
mlx_texture_t	*
	modlx_load_xpm42(
		const char *path)
{
	mlx_texture_t	*texture;
	xpm_t			*xpm;

	xpm = mlx_load_xpm42(path);
	if (xpm == NULL)
	{
		set_error(CUB_MLXFAIL);
		return (NULL);
	}
	texture = modlx_texdup(&xpm->texture);
	mlx_delete_xpm42(xpm);
	if (texture == NULL)
	{
		set_error(CUB_MEMFAIL);
		return (NULL);
	}
	return (texture);
}

// copied from mlx library, modified for norm, for some reason font isn't public
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
		y++;
	}
}

// writes new string in existent mlx_image_t created by mlx_put_string()
// fails if new string is longer than original
int
	modlx_put_string(
		mlx_image_t *strimage,
		const char *str)
{
	int32_t			imgoffset;
	const size_t	len = ft_strlen(str);
	size_t			i;

	if (len * FONT_WIDTH > strimage->width)
		return (RETURN_FAILURE);
	imgoffset = 0;
	i = 0;
	while (i < len)
	{
		mlx_draw_char(strimage, mlx_get_texoffset(str[i]), imgoffset);
		imgoffset += FONT_WIDTH;
		i++;
	}
	return (RETURN_SUCCESS);
}

// copies pixelbuffer from one mlx_image_t to another
//	to avoid improper usage of MLX42 owned memory
mlx_image_t	*
	modlx_imgcpy(
		mlx_image_t *dest,
		mlx_image_t *src)
{
	size_t	pixelcount;

	if (dest == NULL || src == NULL)
		return (NULL);
	pixelcount = src->width * src->height;
	ft_memcpy(dest->pixels, src->pixels, pixelcount * sizeof(uint32_t));
	return (dest);
}
