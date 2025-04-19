/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_menu.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/22 19:48:30 by simon         #+#    #+#                 */
/*   Updated: 2025/04/18 23:33:18 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int
	init_menu_background(
		t_window *window,
		t_scalable *background)
{
	mlx_t	*mlx;

	mlx = window->mlx;
	background->texture = mlx_load_png(MENU_BACKGROUND_PATH);
	if (background->texture == NULL)
		return (set_error(CUB_MLXFAIL));
	if (add_to_texture_list(window, background->texture) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	background->scale = 1;
	background->scale = ft_max_float(
			1.0 * mlx->width / background->texture->width,
			1.0 * mlx->height / background->texture->height);
	return (RETURN_SUCCESS);
}

static int
	init_menu_button(
		t_window *window,
		t_scalable *button,
		const char *path)
{
	mlx_t	*mlx;

	mlx = window->mlx;
	button->texture = &mlx_load_xpm42(path)->texture;
	if (button->texture == NULL)
		return (set_error(CUB_MLXFAIL));
	if (add_to_texture_list(window, button->texture) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	button->scale = 1;
	button->scale = ft_min_float(
			1.0 * (mlx->width / 3) / button->texture->width,
			1.0 * (mlx->height / 10) / button->texture->height);
	return (RETURN_SUCCESS);
}

static int
	init_menu_structs(
		t_window *window,
		t_menu *menu)
{
	if (init_menu_background(window, &menu->background) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	if (init_menu_button(window, &menu->buttons[MENU_B_START_INDEX],
			MENU_B_START_PATH) != RETURN_SUCCESS
		|| init_menu_button(window, &menu->buttons[MENU_B_QUIT_INDEX],
			MENU_B_QUIT_PATH) != RETURN_SUCCESS
		|| init_menu_button(window, &menu->highlight,
			MENU_B_HIGHLIGHT_PATH) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	menu->buttons_x_offset
		= window->mlx->width / 2
		- menu->highlight.texture->width * menu->highlight.scale / 2;
	menu->buttons_y_margin
		= menu->highlight.texture->height * menu->highlight.scale;
	menu->buttons_y_offset
		= window->mlx->height / 2
		- menu->buttons_y_margin * MENU_B_COUNT;
	menu->selection = 0;
	return (RETURN_SUCCESS);
}

int
	new_images_menu(
		mlx_t *mlx,
		t_menu *menu)
{
	size_t	i;

	if (new_scaled_image(mlx, &menu->background) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	if (mlx_image_to_window(mlx, menu->background.image, 0, 0) < 0)
		return (set_error(CUB_MLXFAIL));
	i = 0;
	while (i < MENU_B_COUNT)
	{
		if (new_scaled_image(mlx, &menu->buttons[i]) != RETURN_SUCCESS)
			return (RETURN_FAILURE);
		if (mlx_image_to_window(mlx, menu->buttons[i].image,
				menu->buttons_x_offset, menu->buttons_y_offset
				+ menu->buttons_y_margin * i * 2) < 0)
			return (set_error(CUB_MLXFAIL));
		++i;
	}
	if (new_scaled_image(mlx, &menu->highlight) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	if (mlx_image_to_window(mlx, menu->highlight.image, 0, 0) < 0)
		return (set_error(CUB_MLXFAIL));
	return (RETURN_SUCCESS);
}

int
	init_menu(
		t_window *window,
		t_menu *menu)
{
	if (init_menu_structs(window, menu) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	if (new_images_menu(window->mlx, menu) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	select_button(menu, MLX_KEY_UP);
	return (RETURN_SUCCESS);
}
