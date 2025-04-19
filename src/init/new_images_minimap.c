/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_images_minimap.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/04 22:26:03 by simon         #+#    #+#                 */
/*   Updated: 2025/04/17 23:07:36 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// for illustrative purposes, set outer circle pixel colour to C_TRANSLUCENT
static void
	sample_overlay(
		mlx_image_t *dest,
		uint32_t x,
		uint32_t y,
		void *param)
{
	const uint32_t	radius = *(uint32_t *)param;
	const int		xcoord = (int)(x - radius);
	const int		ycoord = (int)(y - radius);

	if (!ft_is_in_circle(xcoord, ycoord, radius))
		((uint32_t *)dest->pixels)[y * dest->width + x] = C_TRANSPARENT;
	else if (!ft_is_in_circle(xcoord, ycoord, radius * 39 / 42))
		((uint32_t *)dest->pixels)[y * dest->width + x] = C_TRANSLUCENT;
	else
		((uint32_t *)dest->pixels)[y * dest->width + x] = C_WALL;
}

static int
	init_minimap_player_icon(
		mlx_t *mlx,
		t_scalable *player,
		t_minimap *minimap)
{
	player->scale = minimap->block_size / player->texture->height;
	player->scale = nearest_power_of_2(player->scale);
	if (new_scaled_image(mlx, player) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	if (mlx_image_to_window(mlx, player->image,
			minimap->walls->instances[0].x + minimap->radius
			- (player->image->width / 2),
			minimap->walls->instances[0].y + minimap->radius
			- (player->image->height / 2)) < 0)
		return (set_error(CUB_MLXFAIL));
	return (RETURN_SUCCESS);
}

int
	new_images_minimap(
		mlx_t *mlx,
		t_minimap *minimap)
{
	minimap->circle_overlay = malloc(sizeof(uint32_t)
			* (pow(minimap->side, 2) + 1) + 1);
	if (minimap->circle_overlay == NULL)
		return (set_error(CUB_MEMFAIL));
	minimap->walls = mlx_new_image(mlx, minimap->side, minimap->side);
	if (minimap->walls == NULL)
		return (set_error(CUB_MLXFAIL));
	if (mlx_image_to_window(mlx, minimap->walls,
			(minimap->side * 0.2), mlx->height - (minimap->side * 1.2)) < 0)
		return (set_error(CUB_MLXFAIL));
	if (init_minimap_player_icon(mlx, &minimap->player, minimap)
		!= RETURN_SUCCESS)
		return (RETURN_FAILURE);
	image_iter(minimap->walls, sample_overlay, &minimap->radius);
	ft_memcpy(minimap->circle_overlay, minimap->walls->pixels,
		minimap->walls->width * minimap->walls->height * sizeof(uint32_t));
	return (RETURN_SUCCESS);
}
