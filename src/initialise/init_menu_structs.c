/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu_structs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/09/16 17:13:03 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static short
	init_menu_background(
		mlx_t *mlx,
		t_scalable *background)
{
	background->texture
		= mlx_load_png(MENU_BACKGROUND_PATH);
	if (background->texture == NULL)
		return (EXIT_FAILURE);
	background->scale = 1;
	background->scale = ft_max_float(
			1.0 * mlx->width / background->texture->width,
			1.0 * mlx->height / background->texture->height);
}

static short
	init_menu_button(
		mlx_t *mlx,
		t_scalable *button,
		const char *path)
{
	button->texture = &mlx_load_xpm42(path)->texture;
	if (button->texture == NULL)
		return (EXIT_FAILURE);
	button->scale = 1;
	button->scale = ft_min_float(
			1.0 * (mlx->width / 3) / button->texture->width,
			1.0 * (mlx->height / 10) / button->texture->height);
}

short
	init_menu_structs(
		t_window *window)
{
	init_menu_background(window->mlx, &window->menu.background);
	init_menu_button(window->mlx,
		&window->menu.button_start, MENU_BUTTON_START_PATH);
	init_menu_button(window->mlx,
		&window->menu.button_quit, MENU_BUTTON_QUIT_PATH);
	return (EXIT_SUCCESS);
}
