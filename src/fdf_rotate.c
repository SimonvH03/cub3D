/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 23:44:02 by simon             #+#    #+#             */
/*   Updated: 2024/04/19 17:39:34 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// angle gamma around z-axis (roll)
static void
	point_rotate_gamma(
		t_point *point,
		const float gamma)
{
	const float	prev_x = point->x;

	point->x = point->x * cos(gamma) + point->y * sin(gamma);
	point->y = prev_x * -sin(gamma) + point->y * cos(gamma);
}

// angle beta around y-axis (yaw)
static void
	point_rotate_beta(
		t_point *point,
		const float beta)
{
	const float	prev_x = point->x;

	point->x = point->x * cos(beta) + point->z * sin(beta);
	point->z = prev_x * -sin(beta) + point->z * cos(beta);
}

// angle alpha round x-axis (pitch)
static void
	point_rotate_alpha(
		t_point *point,
		const float alpha)
{
	const float	prev_y = point->y;

	point->y = point->y * cos(alpha) + point->z * sin(alpha);
	point->z = prev_y * -sin(alpha) + point->z * cos(alpha);
}

// from project.c / project()
void
	cub3d_rotate(
		void *param,
		const int y,
		const int x)
{
	const t_cub3d	*cub3d = param;
	t_point		*point;

	point = &cub3d->scene->project[y][x];
	if (cub3d->perspective.gamma)
		point_rotate_gamma(point, cub3d->perspective.gamma);
	if (cub3d->perspective.beta)
		point_rotate_beta(point, cub3d->perspective.beta);
	if (cub3d->perspective.alpha)
		point_rotate_alpha(point, cub3d->perspective.alpha);
}
