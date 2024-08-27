/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_scale.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:59:22 by simon             #+#    #+#             */
/*   Updated: 2024/04/19 17:39:34 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// from project.c / project()
void
	cub3d_scale(
		void *param,
		int y,
		int x)
{
	const t_cub3d	*cub3d = param;
	t_point		*point;

	point = &cub3d->scene->project[y][x];
	point->x *= cub3d->scale.diff;
	point->y *= cub3d->scale.diff;
	point->z *= cub3d->scale.diff;
}
