/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 23:30:28 by simon             #+#    #+#             */
/*   Updated: 2024/08/28 01:35:53 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void
	rotate_camera(
		t_camera *camera)
{
	const double	prev_x = camera->dir_x;
	const double	prev_plane_x = camera->plane_x;
	const double	alpha_sin = camera->precalc.a_sin * camera->precalc.sign_alpha;

	if (!camera->precalc.sign_alpha)
		return ;
	camera->dir_x = camera->dir_x * camera->precalc.a_cos + camera->dir_y * alpha_sin;
	camera->dir_y = prev_x * -alpha_sin + camera->dir_y * camera->precalc.a_cos;
	camera->plane_x = camera->plane_x * camera->precalc.a_cos + camera->plane_y * alpha_sin;
	camera->plane_y = prev_plane_x * -alpha_sin + camera->plane_y * camera->precalc.a_cos;
	camera->precalc.sign_alpha = 0;
}

