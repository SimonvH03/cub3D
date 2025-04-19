/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scalable.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/04 22:26:03 by simon         #+#    #+#                 */
/*   Updated: 2025/04/16 23:17:15 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	sample_scalable(
		mlx_image_t *dest,
		uint32_t img_x,
		uint32_t img_y,
		void *param)
{
	const t_scalable	*scalable = (t_scalable *)param;
	const mlx_texture_t	*texture = scalable->texture;
	const float			x = img_x / scalable->scale;
	const float			y = img_y / scalable->scale;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return ;
	((uint32_t *)dest->pixels)[img_y * dest->width + img_x]
		= ((uint32_t *)texture->pixels)[(int)y * texture->width + (int)x];
}

int
	new_scaled_image(
		mlx_t *mlx,
		t_scalable *dest)
{
	dest->image = mlx_new_image(mlx,
			dest->texture->width * dest->scale,
			dest->texture->height * dest->scale);
	if (dest->image == NULL)
		return (set_error(CUB_MLXFAIL));
	image_iter(dest->image, sample_scalable, dest);
	return (RETURN_SUCCESS);
}
