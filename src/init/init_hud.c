/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_hud.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/22 19:48:30 by simon         #+#    #+#                 */
/*   Updated: 2025/04/21 22:05:28 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int
	init_minimap_struct(
		t_hud *hud,
		t_minimap *minimap,
		mlx_t *mlx,
		t_window *window)
{
	minimap->player.texture = hud->player;
	minimap->r_camera = &window->player.camera;
	minimap->r_grid = &window->scene.grid;
	minimap->side = ft_min_float(mlx->height, mlx->width) / 3;
	minimap->block_size = (minimap->side / MINIMAP_SCALE)
		* (mlx->width / (float)mlx->height);
	minimap->radius = minimap->side / 2;
	return (RETURN_SUCCESS);
}

static int
	init_bigmap_struct(
		t_hud *hud,
		t_bigmap *bigmap,
		mlx_t *mlx,
		t_window *window)
{
	bigmap->player_icon_src.texture = hud->player;
	bigmap->r_camera = &window->player.camera;
	bigmap->r_grid = &window->scene.grid;
	bigmap->block_size = ft_min_float(
			mlx->height / (window->scene.grid.y_max + 2),
			mlx->width / (window->scene.grid.x_max + 2));
	bigmap->x_offset = mlx->width
		- window->scene.grid.x_max * bigmap->block_size;
	bigmap->y_offset = mlx->height
		- window->scene.grid.y_max * bigmap->block_size;
	bigmap->x_offset /= 2;
	bigmap->y_offset /= 2;
	return (RETURN_SUCCESS);
}

int
	init_hud(
		t_window *window,
		t_hud *hud)
{
	mlx_t	*mlx;

	mlx = window->mlx;
	hud->player = &mlx_load_xpm42(PLAYER_ICON_PATH)->texture;
	if (hud->player == NULL)
		return (set_error(CUB_MLXFAIL));
	if (add_to_texture_list(window, hud->player) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	init_bigmap_struct(hud, &hud->bigmap, mlx, window);
	init_minimap_struct(hud, &hud->minimap, mlx, window);
	if (new_images_bigmap(mlx, &hud->bigmap) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	if (new_images_minimap(mlx, &hud->minimap) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	hud->fps.image = mlx_put_string(mlx, "00000",
			(mlx->width / 2) - (MLX_FONT_WIDTH * 1.5), mlx->height / 42);
	if (hud->fps.image == NULL)
		return (set_error(CUB_MLXFAIL));
	return (RETURN_SUCCESS);
}
