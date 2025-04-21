/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transpose_texture.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/18 20:16:47 by simon         #+#    #+#                 */
/*   Updated: 2025/04/21 14:34:33 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
