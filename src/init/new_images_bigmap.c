/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_images_bigmap.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/04 22:26:03 by simon         #+#    #+#                 */
/*   Updated: 2025/04/21 21:53:18 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	sample_bigmap(
		mlx_image_t *dest,
		uint32_t img_x,
		uint32_t img_y,
		void *param)
{
	const t_bigmap	*bigmap = (t_bigmap *)param;
	const t_grid	*grid = bigmap->r_grid;
	float			x;
	float			y;

	x = img_x;
	y = img_y;
	x -= dest->width / (float)2;
	y -= dest->height / (float)2;
	x /= bigmap->block_size;
	y /= bigmap->block_size;
	x += grid->x_max / (float)2;
	y += grid->y_max / (float)2;
	if (x < 0 || x >= grid->x_max || y < 0 || y >= grid->y_max)
		((uint32_t *)dest->pixels)[img_y * dest->width + img_x] = C_TRANSLUCENT;
	else if (get_type(grid->tilemap[(int)y][(int)x]) == ' ')
		((uint32_t *)dest->pixels)[img_y * dest->width + img_x] = C_TRANSLUCENT;
	else if (is_door(grid->tilemap[(int)y][(int)x]))
		((uint32_t *)dest->pixels)[img_y * dest->width + img_x] = C_DOOR;
	else if (is_solid(grid->tilemap[(int)y][(int)x]))
		((uint32_t *)dest->pixels)[img_y * dest->width + img_x] = C_WALL;
	else
		((uint32_t *)dest->pixels)[img_y * dest->width + img_x] = C_FLOOR;
}

static int
	init_bigmap_player_icon(
		mlx_t *mlx,
		t_scalable *player_icon,
		t_bigmap *bigmap)
{
	player_icon->scale = bigmap->block_size / player_icon->texture->height;
	player_icon->scale = nearest_power_of_2(player_icon->scale);
	if (new_scaled_image(mlx, player_icon) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	bigmap->player = mlx_new_image(mlx,
			player_icon->image->width, player_icon->image->height);
	if (bigmap->player == NULL)
		return (set_error(CUB_MLXFAIL));
	if (mlx_image_to_window(mlx, bigmap->player, 0, 0) < 0)
		return (set_error(CUB_MLXFAIL));
	return (RETURN_SUCCESS);
}

int
	new_images_bigmap(
		mlx_t *mlx,
		t_bigmap *bigmap)
{
	bigmap->walls = mlx_new_image(mlx, mlx->width, mlx->height);
	if (bigmap->walls == NULL)
		return (set_error(CUB_MLXFAIL));
	if (mlx_image_to_window(mlx, bigmap->walls, 0, 0) < 0)
		return (set_error(CUB_MLXFAIL));
	if (init_bigmap_player_icon(mlx, &bigmap->player_icon_src, bigmap)
		!= RETURN_SUCCESS)
		return (RETURN_FAILURE);
	bigmap->x_offset -= bigmap->player->width / 2;
	bigmap->y_offset -= bigmap->player->height / 2;
	set_bigmap_ability(bigmap, false);
	image_iter(bigmap->walls, sample_bigmap, bigmap);
	return (RETURN_SUCCESS);
}
