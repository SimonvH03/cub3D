/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_frametime.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <svan-hoo@student.codam.nl>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/31 18:33:20 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/04/21 21:46:30 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	update_fps_image(
		double delta_time,
		t_fps *fps)
{
	char		buffer[12];
	uint32_t	output_fps;

	ft_bzero(buffer, 12);
	fps->cum_time += delta_time;
	++fps->no_frames;
	if (fps->cum_time < 0.08)
		return ;
	output_fps = roundf(fps->no_frames / fps->cum_time);
	fps->cum_time = 0;
	fps->no_frames = 0;
	if (output_fps > 99999)
		output_fps = 99999;
	ft_putnbr_ptr(buffer, output_fps);
	ft_bzero(fps->image->pixels,
		fps->image->width * fps->image->height * sizeof(uint32_t));
	modlx_put_string(fps->image, buffer);
}

void
	frametime_dependant_variables(
		void *param)
{
	t_window	*window;
	double		delta_time;
	t_camera	*camera;

	window = (t_window *)param;
	delta_time = window->mlx->delta_time;
	camera = &window->player.camera;
	update_fps_image(window->mlx->delta_time, &window->hud.fps);
	camera->movement_speed = MOVEMENT_SPEED * delta_time;
	if (camera->movement_speed > 0.5f)
		camera->movement_speed = 0.5f;
	camera->rotation_cosin[0] = cosf(ROTATION_SPEED * delta_time);
	camera->rotation_cosin[1] = sinf(ROTATION_SPEED * delta_time);
	camera->cursor_rot_speed = CURSOR_ROT_SPEED * delta_time;
}
