/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   normalize_vector2.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:51:01 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/04/16 15:24:22 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float
	quake3_heavilyinspired_rsqrt(
		float number)
{
	const float	threehalfs = 1.5f;
	const float	a = number * 0.5f;
	float		b;
	t_q3		cast;

	b = number;
	cast.as_float = b;
	cast.as_int = 0x5f3759df - (cast.as_int >> 1);
	b = cast.as_float;
	b = b * (threehalfs - (a * b * b));
	b = b * (threehalfs - (a * b * b));
	return (b);
}

void	normalize_vector2(float *x_component, float *y_component)
{
	const float		dx = *x_component;
	const float		dy = *y_component;
	const double	inverse_sqrt
		= quake3_heavilyinspired_rsqrt((dx * dx) + (dy * dy));

	*x_component *= ft_abs_float(inverse_sqrt);
	*y_component *= ft_abs_float(inverse_sqrt);
}
