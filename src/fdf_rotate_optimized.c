/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_rotate_optimized.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 23:30:28 by simon             #+#    #+#             */
/*   Updated: 2024/04/19 17:39:34 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void
	point_rotate_precalculated(
		const t_cub3d *cub3d,
		t_point *point)
{
	float			prev_x;
	float			prev_y;
	const float	gamma_sin = cub3d->cosin.a_sin * cub3d->precalc.gamma;
	const float	beta_sin = cub3d->cosin.a_sin * cub3d->precalc.beta;
	const float	alpha_sin = cub3d->cosin.a_sin * cub3d->precalc.alpha;

	if (cub3d->precalc.gamma)
	{
		prev_x = point->x;
		point->x = point->x * cub3d->cosin.a_cos + point->y * gamma_sin;
		point->y = prev_x * -gamma_sin + point->y * cub3d->cosin.a_cos;
	}
	if (cub3d->precalc.beta)
	{
		prev_x = point->x;
		point->x = point->x * cub3d->cosin.a_cos + point->z * beta_sin;
		point->z = prev_x * -beta_sin + point->z * cub3d->cosin.a_cos;
	}
	if (cub3d->precalc.alpha)
	{
		prev_y = point->y;
		point->y = point->y * cub3d->cosin.a_cos + point->z * alpha_sin;
		point->z = prev_y * -alpha_sin + point->z * cub3d->cosin.a_cos;
	}
}

// from project.c / project()
void
	cub3d_rotate_optimized(
		void *param,
		const int y,
		const int x)
{
	const t_cub3d	*cub3d = param;
	t_point		*point;

	point = &cub3d->scene->project[y][x];
	if (cub3d->precalc.gamma || cub3d->precalc.beta || cub3d->precalc.alpha)
		point_rotate_precalculated(cub3d, point);
}
