/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   modlx.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/28 22:07:27 by simon         #+#    #+#                 */
/*   Updated: 2025/04/22 17:49:01 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory_cub3d.h"

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

// sets texture column-major (transposes over y = x)
int
	transpose_texture(
		mlx_texture_t *texture)
{
	const size_t	pixelcount = texture->width * texture->height;
	uint32_t		*pixelcopy;
	uint32_t		y;
	uint32_t		x;

	pixelcopy = malloc(sizeof(uint32_t) * pixelcount);
	if (pixelcopy == NULL)
		return (set_error(CUB_MEMFAIL));
	ft_memcpy(pixelcopy, texture->pixels, sizeof(uint32_t) * pixelcount);
	y = 0;
	while (y < texture->height)
	{
		x = 0;
		while (x < texture->width)
		{
			((uint32_t *)texture->pixels)[(y * texture->width + x)]
				= pixelcopy[(x * texture->height + y)];
			x++;
		}
		y++;
	}
	free(pixelcopy);
	return (RETURN_SUCCESS);
}
