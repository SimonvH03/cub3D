/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:05:56 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/26 18:05:12 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void
	cub3d_redraw(
		t_cub3d *cub3d)
{
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_R)
		|| mlx_is_key_down(cub3d->mlx, MLX_KEY_UP)
		|| mlx_is_key_down(cub3d->mlx, MLX_KEY_DOWN)
		|| mlx_is_key_down(cub3d->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(cub3d->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(cub3d->mlx, MLX_KEY_C)
		|| mlx_is_key_down(cub3d->mlx, MLX_KEY_H)
		|| mlx_is_key_down(cub3d->mlx, MLX_KEY_T))
		cub3d->redraw = true;
	if (cub3d->perspective.reproject
		|| cub3d->precalc.reproject
		|| cub3d->scale.diff != 1)
		cub3d->redraw = true;
}

// using only negative and positive because manual
//;rotations are done with precalculated values
static void
	manual_rotation(
		t_cub3d	*cub3d)
{
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_Q))
		cub3d->precalc.gamma = +cub3d->precalc.sign;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_E))
		cub3d->precalc.gamma = -cub3d->precalc.sign;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
		cub3d->precalc.beta = -cub3d->precalc.sign;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
		cub3d->precalc.beta = +cub3d->precalc.sign;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
		cub3d->precalc.alpha = -cub3d->precalc.sign;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
		cub3d->precalc.alpha = +cub3d->precalc.sign;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub3d->mlx);
	if (cub3d->precalc.gamma
		|| cub3d->precalc.beta
		|| cub3d->precalc.alpha)
		cub3d->precalc.reproject = true;
}

static void
	manual_translation(
		t_cub3d	*cub3d)
{
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_UP))
		cub3d->offset.y -= 10 * cub3d->precalc.sign;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_DOWN))
		cub3d->offset.y += 10 * cub3d->precalc.sign;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_LEFT))
		cub3d->offset.x -= 10 * cub3d->precalc.sign;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_RIGHT))
		cub3d->offset.x += 10 * cub3d->precalc.sign;
}

// because bigger maps are slow, press + to get somewhere quick
static void
	inputs_variable_speed(
		t_cub3d	*cub3d)
{
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_MINUS))
	{
		if (cub3d->speed > 0.00001)
			cub3d->speed *= 0.95;
		cub3d->cosin = (t_cosin){cos(cub3d->speed), sin(cub3d->speed)};
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_EQUAL))
	{
		if (cub3d->speed < PI)
			cub3d->speed *= 1.05;
		else
			cub3d->speed = ROTATION_SPEED;
		cub3d->cosin = (t_cosin){cos(cub3d->speed), sin(cub3d->speed)};
	}
}

// from main.c loop_hooks()
// do 'em all at once, doesn't matter
void
	user_inputs(
		void	*param)
{
	t_cub3d	*cub3d;

	cub3d = param;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_P)
		|| mlx_is_key_down(cub3d->mlx, MLX_KEY_I))
		input_presets_flat(cub3d);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_O)
		|| mlx_is_key_down(cub3d->mlx, MLX_KEY_U))
		input_presets_balls(cub3d);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_MINUS)
		|| mlx_is_key_down(cub3d->mlx, MLX_KEY_EQUAL))
		inputs_variable_speed(cub3d);
	manual_rotation(cub3d);
	manual_translation(cub3d);
	cub3d_redraw(cub3d);
}
