/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   select_button.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/16 23:36:30 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/02/24 01:19:11 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool
	is_in_image(
		mlx_image_t *image,
		int32_t instance_id,
		int32_t x,
		int32_t y)
{
	const int32_t	lower_x = image->instances[instance_id].x;
	const int32_t	lower_y = image->instances[instance_id].y;
	const int32_t	upper_x = lower_x + image->width;
	const int32_t	upper_y = lower_y + image->height;

	if (x > lower_x && x < upper_x
		&& y > lower_y && y < upper_y)
		return (true);
	return (false);
}

void
	hover_button(
		t_menu *menu,
		t_window *window)
{
	mlx_image_t	*button;
	int32_t		x;
	int32_t		y;
	size_t		i;

	mlx_get_mouse_pos(window->mlx, &x, &y);
	i = 0;
	while (i < MENU_B_COUNT)
	{
		button = menu->buttons[i].image;
		if (is_in_image(button, 0, x, y))
		{
			menu->selection = i;
			menu->highlight.image->instances[0].x = button->instances[0].x;
			menu->highlight.image->instances[0].y = button->instances[0].y;
		}
		i++;
	}
}

void
	click_button(
		t_menu *menu,
		t_window *window)
{
	int32_t	x;
	int32_t	y;

	mlx_get_mouse_pos(window->mlx, &x, &y);
	if (is_in_image(menu->buttons[MENU_B_START_INDEX].image, 0, x, y))
		toggle_view(window);
	else if (is_in_image(menu->buttons[MENU_B_QUIT_INDEX].image, 0, x, y))
		mlx_close_window(window->mlx);
}

void
	select_button(
		t_menu *menu,
		keys_t key)
{
	if (key == MLX_KEY_UP && menu->selection > 0)
		menu->selection -= 1;
	if (key == MLX_KEY_DOWN && menu->selection < MENU_B_COUNT - 1)
		menu->selection += 1;
	menu->highlight.image->instances[0].x
		= menu->buttons[menu->selection].image->instances[0].x;
	menu->highlight.image->instances[0].y
		= menu->buttons[menu->selection].image->instances[0].y;
}

void
	confirm_selection(
		t_menu *menu,
		t_window *window)
{
	if (menu->selection == MENU_B_START_INDEX)
		toggle_view(window);
	if (menu->selection == MENU_B_QUIT_INDEX)
		mlx_close_window(window->mlx);
}
