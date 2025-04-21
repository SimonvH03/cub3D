/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_controls.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/06 23:30:28 by simon         #+#    #+#                 */
/*   Updated: 2025/04/21 21:56:05 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	mouse_buttons(
		mouse_key_t button,
		action_t action,
		modifier_key_t mods,
		void *param)
{
	t_window	*window;

	window = (t_window *)param;
	(void)mods;
	if (window->view == wv_menu)
	{
		if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
			click_button(&window->menu, window);
	}
	else if (window->view == wv_game)
	{
		if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
			fire_weapon(&window->player.weapon);
	}
}

void
	mouse_pan(
		mlx_t *mlx,
		t_camera *camera)
{
	float	horizontal_displacement;
	float	vertical_displacement;
	int32_t	x_pos;
	int32_t	y_pos;

	mlx_get_mouse_pos(mlx, &x_pos, &y_pos);
	mlx_set_mouse_pos(mlx, mlx->width / 2, mlx->height / 2);
	if (x_pos != mlx->width / 2)
	{
		horizontal_displacement = x_pos / (float)mlx->width - 0.5f;
		horizontal_displacement *= camera->cursor_rot_speed;
		camera->dir_x += camera->plane_x * horizontal_displacement;
		camera->dir_y += camera->plane_y * horizontal_displacement;
		normalize_vector2(&camera->dir_x, &camera->dir_y);
		camera->plane_x = CAMERA_PLANE * camera->aspect_ratio * -camera->dir_y;
		camera->plane_y = CAMERA_PLANE * camera->aspect_ratio * camera->dir_x;
	}
	if (y_pos != mlx->height / 2)
	{
		vertical_displacement = mlx->height / 2 - (int32_t)y_pos;
		camera->height_offset -= vertical_displacement;
		camera->height_offset = ft_clamp(camera->height_offset, 0, mlx->height);
	}
}
