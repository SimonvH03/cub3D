/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu_images.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/09/18 17:52:37 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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
		mlx_t *mlx,
		t_menu *menu)
{
	size_t	i;

	if (new_scaled_image(mlx, &menu->background) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(mlx, menu->background.image, 0, 0) < 0)
		return (EXIT_FAILURE);
	i = 0;
	while (i < MENU_B_COUNT)
	{
		if (new_scaled_image(mlx, &menu->buttons[i]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (mlx_image_to_window(mlx, menu->buttons[i].image,
				menu->buttons_x_offset, menu->buttons_y_offset
				+ menu->buttons_y_margin * i * 2) < 0)
			return (EXIT_FAILURE);
		++i;
	}
	if (new_scaled_image(mlx, &menu->highlight) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(mlx, menu->highlight.image, 0, 0) < 0)
		return (EXIT_FAILURE);
	up_down_select(menu);
	return (EXIT_SUCCESS);
}

short
	init_menu_images(
		mlx_t *mlx,
		t_menu *menu)
{
	if (new_images_menu(mlx, menu) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	draw_scaled_image(&menu->background);
	draw_scaled_image(&menu->highlight);
	draw_scaled_image(&menu->buttons[MENU_B_START_INDEX]);
	draw_scaled_image(&menu->buttons[MENU_B_QUIT_INDEX]);
	return (EXIT_SUCCESS);
}
