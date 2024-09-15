/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_init_menu_images.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/09/15 19:23:05 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static short
	new_scaled_image(
		mlx_t *mlx,
		t_scalable *dest)
{
	dest->image = mlx_new_image(mlx,
		dest->texture->width * dest->scale,
		dest->texture->height * dest->scale);
	if (dest->image == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

short
	new_images_menu(
		t_window *window,
		t_menu *menu)
{
	uint32_t		button_x_offset;
	uint32_t		button_y_offset;
	uint32_t		button_y_margin;

	if (new_scaled_image(window->mlx, &menu->background) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (new_scaled_image(window->mlx, &menu->button_start) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (new_scaled_image(window->mlx, &menu->button_quit) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	button_x_offset = window->mlx->width / 2
		- menu->button_start.image->width / 2;
	button_y_offset = window->mlx->height / 2
		- menu->button_start.image->height / 2;
	button_y_margin = menu->button_start.image->height;
	if (mlx_image_to_window(window->mlx, menu->background.image, 0, 0) < 0)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(window->mlx, menu->button_start.image,
			button_x_offset, button_y_offset - button_y_margin) < 0)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(window->mlx, menu->button_quit.image,
			button_x_offset, button_y_offset + button_y_margin) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

short
	init_menu_images(
		t_window *window)
{
	if (new_images_menu(window, &window->menu) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	draw_scaled_image(&window->menu.background);
	draw_scaled_image(&window->menu.button_start);
	draw_scaled_image(&window->menu.button_quit);
	return (EXIT_SUCCESS);
}
